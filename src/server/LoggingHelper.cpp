//
// Created by Guillaume on 25/12/2017.
//

#include <ClientMessage.hh>
#include <ServerMessage.hh>
#include "LoggingHelper.hh"
#include "../common/Toolbox.hh"
#include "user/RegisteredUsers.hh"
#include "user/FullUser.hh"
#include "game/planet/Planet.hh"
#include "LoadedData.hh"

bl::server::LoggingHelper::LoggingHelper(const std::shared_ptr<bl::network::socket::TcpBoostSslSocket> &m_socket, ::bl::server::LoadedData &data) : m_socket(m_socket), m_data(data) {

}

bool bl::server::LoggingHelper::executeCommand(std::string const &cmd) {
	bool hasLogged = false;
	network::client::ClientMessage message;
	std::cout << "Received " << cmd << std::endl;
	{
		/*std::cout << "Creating stringstream" << std::endl;
		std::stringstream ss(cmd);
		std::cout << "Creating archive" << std::endl;
		cereal::JSONInputArchive inArchive(ss);
		std::cout << "Filling message" << std::endl;
		inArchive(message);
		std::cout << "Message filled" << std::endl;*/
		message.deserialize(cmd);
	}
	network::server::ServerMessage answer;
	std::cout << "Received " << message.getBody().message << std::endl;
	message.getBody().message = message.getBody().message.substr(1);
	auto toks = common::Toolbox::split(message.getBody().message, "&");
	switch (message.getBody().code) {
		case 22:
			if (toks.size() == 1) {
				auto dbData = m_db.getByKey("users", "login", toks[0]);
				if (dbData != nullptr) {
					user::FullUser user;
					user.deserialize(dbData);
					answer.getBody().type = network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK;
					answer.getBody().code = 22;
					answer.getBody().message = user.getSalt();
				} else {
					answer.getBody().type = network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO;
					answer.getBody().code = 22;
					answer.getBody().message = "Unknown login and / or password";
				}
			}
		case 42:
			if (toks.size() == 2) {
				answer = loginUser(toks);
				if (answer.getBody().type == network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK)
					hasLogged = true;
			} else {
				answer.getBody().type = network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO;
				answer.getBody().code = 42;
				answer.getBody().message = "Invalid login request";
			}
			break;
		case 43:
			if (toks.size() == 6) {
				answer = registerNewUser(toks);
			} else {
				answer.getBody().type = network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO;
				answer.getBody().code = 43;
				answer.getBody().message = "Invalid register request";
			}
			break;
		default:
			answer.getBody().type = network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ERROR;
			answer.getBody().code = 403;
			answer.getBody().message = "You're not logged in yet";
			break;
	}

	/*std::stringstream ss;
	cereal::JSONOutputArchive outArchive(ss);
	outArchive(answer);
	const std::string &strRepresentation = ss.str();
	std::vector<char> fullData(strRepresentation.begin(), strRepresentation.end());
	std::cout << "Sending " << answer << std::endl;
	m_socket->send(std::string(fullData.begin(), fullData.end()));*/
	m_socket->send(answer.serialize());
	return hasLogged;
}

bl::network::server::ServerMessage bl::server::LoggingHelper::registerNewUser(std::vector<std::string> const& toks) {
	network::server::ServerMessage message;
	message.getBody().type = network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO;
	message.getBody().code = 43;
	if (toks[4] != toks[5]) {
		std::cout << "Un-matching passwords" << std::endl;
		message.getBody().message = "Password must match";
	} else if (m_db.getByKey("users", "login", toks[2]) != nullptr) {
		std::cout << "Login already in db" << std::endl;
		message.getBody().message = "Login already in use !";
	} else if (m_db.getByKey("users", "email", toks[3]) != nullptr) {
		std::cout << "Email already in db" << std::endl;
		message.getBody().message = "Email address already in use !";
	} else {
		message.getBody().type = network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK;
		std::cout << "Registering a new user" << std::endl;
		user::FullUser newUser;
		newUser.setFirstname(toks[0]);
		newUser.setLastname(toks[1]);
		newUser.setLogin(toks[2]);
		newUser.setEmail(toks[3]);
		newUser.setSalt(common::Toolbox::generateSalt(this->m_saltSize));
		newUser.setPassword(common::Toolbox::sha512This(newUser.getSalt() + toks[4]));
		std::cout << "New user built" << std::endl;

		game::planet::Planet startingPlanet;
		startingPlanet.claimBy(newUser);
		newUser.setLastPlanetId(startingPlanet.getUuidAsString());
		std::cout << "New planet built" << std::endl;

		try {
			m_db.update("planets", "uuid", startingPlanet.getUuidAsString(), startingPlanet.serialize());
			m_db.update("users", "uuid", newUser.getUuidAsString(), newUser.serialize());
		} catch (std::exception &e) {
			std::cerr << "Update failure: " << e.what() << std::endl;
		}
		std::cout << "User and planet saved" << std::endl;
	}
	std::cout << "Returning message" << std::endl;
	return message;
}

bl::network::server::ServerMessage bl::server::LoggingHelper::loginUser(std::vector<std::string> const &toks) {
	network::server::ServerMessage answer;
	nlohmann::json dbData;
	answer.getBody().type = network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO;
	answer.getBody().code = 42;

	dbData = m_db.getByKey("users", "login", toks[0]);
	if (dbData != nullptr) {
		user::FullUser fullUser;
		fullUser.deserialize(dbData);
		std::cout << "User salt is " << fullUser.getSalt() << std::endl;
		if (fullUser.getPassword() == common::Toolbox::sha512This(fullUser.getSalt() + toks[1])) {
			if (m_data.loggedUsers.find(fullUser.getLogin()) != m_data.loggedUsers.end()) {
				answer.getBody().message = "You're already logged in !";
			} else {
				answer.getBody().type = network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK;
				std::shared_ptr<user::User> user = std::make_shared<user::User>(fullUser);
				std::shared_ptr<user::SessionIdentifier> session{new user::SessionIdentifier()};
				session->setUser(user);
				answer.getBody().message = session->getUuidAsString();
				this->m_data.activeSessions.emplace(session->getUuidAsString(), session);
				this->m_data.loggedUsers.insert(user->getLogin());
				this->m_data.activeUsers.emplace(user->getUuidAsString(), user);

				std::cout << "Registering session " << session->getUuidAsString() << " for user " << user->getLogin() << std::endl;

				dbData = m_db.getByKey("planets", "uuid", user->getLastPlanetId());
				std::shared_ptr<game::planet::Planet> planet{new game::planet::Planet()};
				planet->deserialize(dbData);
				this->m_data.loadedPlanets.emplace(planet->getUuidAsString(), planet);

				std::cout << "Loading planet " << planet->getUuidAsString() << std::endl;
			}
		} else {
			answer.getBody().message = "Login and password don't match";
		}
	} else {
		answer.getBody().message = "Unknown login and / or password";
	}

	return answer;
}
