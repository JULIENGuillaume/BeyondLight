//
// Created by Guillaume on 21/11/2017.
//

#ifndef BEYONDLIGHT_CLIENT_NETWORKWRAPPER_HH
#define BEYONDLIGHT_CLIENT_NETWORKWRAPPER_HH


#include <PSingleton.hpp>
#include <ISocket.hh>

class NetworkWrapper {
public:
	static std::shared_ptr<bl::network::socket::ISocket> m_socket;
};

//std::shared_ptr<network::socket::ISocket> NetworkWrapper::m_socket = nullptr;

#endif //BEYONDLIGHT_CLIENT_NETWORKWRAPPER_HH
