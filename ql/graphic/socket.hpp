#pragma once

#include <ql/core/definition/definition.hpp>
#if defined QL_SFML

#include <SFML/Network.hpp>
#include <string>

namespace ql
{
	struct socket
	{
		QL_SOURCE void set_address(sf::IpAddress address, ql::u32 port);
		QL_SOURCE void connect(sf::IpAddress address, ql::u32 port);
		QL_SOURCE void connect();
		QL_SOURCE void connect_until_connected();
		QL_SOURCE void send(std::string data);
		QL_SOURCE void send_and_check_sent_size(std::string data);
		QL_SOURCE bool listen(ql::u32 port, sf::IpAddress address = sf::IpAddress::Any);
		QL_SOURCE bool accept(socket& other);
		QL_SOURCE std::string receive();
		QL_SOURCE void disable_blocking();
		QL_SOURCE void enable_blocking();
		QL_SOURCE bool is_blocking_enabled() const;
		QL_SOURCE bool is_connected() const;

		bool connected = false;
		bool address_set = false;
		sf::TcpSocket socket;
		sf::TcpListener listener;

		ql::u32 port = 0u;
		sf::IpAddress ip_address = sf::IpAddress::LocalHost;
	};
}	 // namespace ql

#endif