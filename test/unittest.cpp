/*
** unittest.cpp for BeyondLight in /home/guillaume/delivery/BeyondLight/unittest.cpp
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Thu Oct 26 16:03:23 2017 Guillaume Julien
** Last update Thu Oct 26 16:03:23 2017 Guillaume Julien
*/

#include <gtest/gtest.h>
#include <thread>
#include <UdpSslAsyncBoostSocket.hh>
#include <SocketFactory.hh>
#include "../src/network/server/BeyondLightServer.hh"
#include "../src/network/client/BeyondLightClient.hh"

void FactoriesInit() {
	bl::network::socket::SocketFactory::getInstance()->registerModel(bl::network::socket::serverKeyUdpSslAsyncBoostSocket,
	                                                             std::shared_ptr<bl::network::socket::ISocket>(
			                                                             new bl::network::socket::UdpSslAsyncBoostSocket()));

	bl::network::socket::SocketFactory::getInstance()->registerModel(bl::network::socket::clientKeyUdpSslAsyncBoostSocket,
	                                                             std::shared_ptr<bl::network::socket::ISocket>(
			                                                             new bl::network::socket::UdpSslAsyncBoostSocket()));
}

void serverLaunch() {
	bl::network::server::BeyondLightServer server(4242);
	server.run();
}

TEST(Network, ClientServerConnection) {
	FactoriesInit();
	std::thread thread(&serverLaunch);
	thread.detach();

	sleep(1);
	bl::network::client::BeyondLightClient client;
	ASSERT_TRUE(client.connectTo("127.0.0.1", 4242));
	client.disconnect();
}

TEST(SimpleAdd, Diff) {
	EXPECT_NE(1, 0 + 2);
}

TEST(SimpleAdd, NoDiff) {
	EXPECT_EQ(2, 0 + 2);
}

TEST(ComplexeAdd, NoDiff) {
	EXPECT_EQ(123, 100 + 20 + 3);
}