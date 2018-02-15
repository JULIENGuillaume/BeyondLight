//
// Created by Guillaume Julien on 13/02/2018.
//

#include <SocketFactory.hh>
#include "LauncherClient.hh"

bl::network::client::LauncherClient::LauncherClient() :  AClientTcp(socket::clientKeyTcpSslBoostSocket){}

void bl::network::client::LauncherClient::mainLoop() {
	while (this->m_running) {
		std::string cmd = this->getLine();
		std::cout << "Launcher got [" << cmd << "]" << std::endl;
	}
}

std::string bl::network::client::LauncherClient::getLine() {
	bool isOpen = true;

	while (isOpen && m_running) {
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
			isOpen = false;
			std::cerr << "Exception while reading (" << e.what() << "), quitting" << std::endl;
		}
	}
	return "";
}

