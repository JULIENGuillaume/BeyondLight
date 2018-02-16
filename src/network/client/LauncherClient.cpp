//
// Created by Guillaume Julien on 13/02/2018.
//

#include <SocketFactory.hh>
#include <fstream>
#include "LauncherClient.hh"
#include "../../common/Toolbox.hh"

bl::network::client::LauncherClient::LauncherClient() :  AClientTcp(socket::clientKeyTcpSslBoostSocket){}

void bl::network::client::LauncherClient::mainLoop() {
	while (this->m_running) {
		std::string cmd = this->getLine();
		std::cout << "Launcher got [" << cmd << "]" << std::endl;
		auto data = common::Toolbox::split(cmd, ":");
		if (data.size() > 1) {
			auto code = std::stol(data[0]);
			switch (code) {
				case 1337:
					std::cerr << "Ending client:" << data[1] << std::endl;
					break;
				case 42:
				{
					std::ofstream outFile(data[1], std::ios::binary);
					auto toRead = static_cast<size_t>(std::stol(data[2]));
					std::string fileData = readSize(toRead);
					std::cout << "Exporting data ! (" << fileData.size() << "o)" << std::endl;
					outFile << fileData;
					std::cout << "Copied " << fileData << std::endl;
					break;
				}
				default:
					std::cout << "Do nothing with " << code << std::endl;
			}
		}
	}
}

std::string bl::network::client::LauncherClient::getLine() {

	while (m_running) {
		try {
			m_data += this->m_socket->receive();
			if (m_data.find(newLineDelim) != m_data.npos) {
				auto line = m_data.substr(0, m_data.find(newLineDelim));
				m_data.erase(0, m_data.find(newLineDelim) + newLineDelim.length());
				if (line.find(this->msgStartHeader) != line.npos) {
					line = line.substr(line.find(this->msgStartHeader) + this->msgStartHeader.size());
				}
				return line;
			}
		} catch (std::exception const &e) {
			m_running = false;
			std::cerr << "Exception while reading (" << e.what() << "), quitting" << std::endl;
		}
	}
	return "";
}

std::string bl::network::client::LauncherClient::readSize(size_t size) {
	while (m_running) {
		try {
			if (m_data.size() < size) {
				m_data += this->m_socket->receive();
			} else {
				std::string line;
				line = m_data.substr(0, size);
				m_data.erase(0, size);
				return line;
			}
		} catch (std::exception const &e) {
			m_running = false;
			std::cerr << "Exception while reading (" << e.what() << "), quitting" << std::endl;
		}
	}
	return std::string();
}

