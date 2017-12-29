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
	auto users = user::RegisteredUsers::getInstance();
	network::client::ClientMessage message;
	{
		std::stringstream ss(cmd);
		cereal::PortableBinaryInputArchive inArchive(ss);
		inArchive(message);
	}
	network::server::ServerMessage answer;
	auto toks = common::Toolbox::split(message.getBody().message, ":");
	switch (message.getBody().code) {
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

	std::stringstream ss;
	cereal::PortableBinaryOutputArchive outArchive(ss);
	outArchive(answer);
	const std::string &strRepresentation = ss.str();
	std::vector<char> fullData(strRepresentation.begin(), strRepresentation.end());
	m_socket->send(std::string(fullData.begin(), fullData.end()));
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
		newUser.setPassword(toks[4]);

		game::planet::Planet startingPlanet;
		startingPlanet.claimBy(newUser);
		newUser.setLastPlanetId(startingPlanet.getUuidAsString());

		m_db.update("planets", "uuid", startingPlanet.getUuidAsString(), startingPlanet.serialize());
		m_db.update("users", "uuid", newUser.getUuidAsString(), newUser.serialize());
	}
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
		if (fullUser.getPassword() == toks[1]) {
			if (m_data.loggedUsers.find(fullUser.getLogin()) != m_data.loggedUsers.end()) {
				answer.getBody().message = "You're already logged in !";
			} else {
				answer.getBody().type = network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK;
				user::User user(fullUser);
				std::shared_ptr<user::SessionIdentifier> session{new user::SessionIdentifier()};
				session->setUser(user);
				answer.getBody().message = session->getUuidAsString();
				this->m_data.activeSessions.emplace(session->getUuidAsString(), session);
				this->m_data.loggedUsers.insert(user.getLogin());

				std::cout << "Registering session " << session->getUuidAsString() << " for user " << user.getLogin() << std::endl;

				dbData = m_db.getByKey("planets", "uuid", user.getLastPlanetId());
				std::shared_ptr<game::planet::Planet> planet{new game::planet::Planet()};
				planet->deserialize(dbData);
				this->m_data.loadedPlanets.emplace(planet->getUuidAsString(), planet);

				std::cout << "Loading planet " << planet->getUuidAsString() << std::endl;
			}
		} else {
			answer.getBody().message = "Login and password don't match";
		}
	} else {
		answer.getBody().message = "Unknown login";
	}

	return answer;
}
