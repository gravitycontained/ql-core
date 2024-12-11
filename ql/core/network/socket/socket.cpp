#include <ql/core/network/socket/socket.hpp>

#if defined QL_SFML

#include <ql/core/system/print/print.hpp>

namespace ql
{
	void ql::socket::set_address(sf::IpAddress address, ql::u32 port)
	{
		this->ip_address = address;
		this->port = port;
		this->address_set = true;
	}

	void ql::socket::connect(sf::IpAddress address, ql::u32 port)
	{
		this->set_address(address, port);
		this->connect();
	}

	void ql::socket::connect()
	{
		if (!this->address_set)
		{
			throw std::exception("ql::socket::connect: neither ip_adress nor port set!");
		}
		auto status = this->socket.connect(this->ip_address, this->port);
		this->connected = (status == sf::Socket::Done);
	}

	void ql::socket::connect_until_connected()
	{
		ql::u32 ctr = 0u;
		while (!this->is_connected())
		{
			++ctr;
			ql::print("[", this->ip_address.toString(), " : ", this->port, "] connection attempt ", ctr, " . . .");

			auto status = this->socket.connect(this->ip_address, this->port);
			this->connected = (status == sf::Socket::Done);
			if (this->connected)
			{
				ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", " done");
			}
			else
			{
				ql::println();
			}
		}
	}

	void ql::socket::send(std::string data)
	{
		if (this->socket.send(data.c_str(), data.size()) != sf::Socket::Done)
		{
			ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", "ql::socket::send: error sending");
		}
	}

	void ql::socket::send_and_check_sent_size(std::string data)
	{
		ql::size sent;
		this->socket.send(data.c_str(), data.size(), sent);
		if (sent != data.size())
		{
			ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", "ql::socket::send: trying to send ", data.size(), " bytes but only ", sent, " bytes arrived");
		}
	}

	bool ql::socket::listen(ql::u32 port, sf::IpAddress address)
	{
		if (this->listener.listen(port, address) != sf::Socket::Done)
		{
			ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", "ql::socket::listen(", address.toString(), ", ", port, ") : error listening");
			return false;
		}
		return true;
	}

	bool ql::socket::accept(ql::socket& other)
	{
		if (this->listener.accept(other.socket) != sf::Socket::Done)
		{
			ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", "ql::socket::accept(", other.ip_address.toString(), ") : error accepting");
			return false;
		}
		return true;
	}

	std::string ql::socket::receive()
	{
		sf::Packet packet;
		if (this->socket.receive(packet) != sf::Socket::Done)
		{
			throw std::exception("ql::socket::receive: error receiving!");
		}

		if (packet.getData())
		{
			std::string result(reinterpret_cast<const char*>(packet.getData()), packet.getDataSize());
		}
		return std::string{};
	}

	void ql::socket::disable_blocking()
	{
		this->socket.setBlocking(false);
		this->listener.setBlocking(false);
	}

	void ql::socket::enable_blocking()
	{
		this->socket.setBlocking(true);
		this->listener.setBlocking(true);
	}

	bool ql::socket::is_blocking_enabled() const
	{
		return this->socket.isBlocking();
	}

	bool ql::socket::is_connected() const
	{
		return this->connected;
	}
}	 // namespace ql

#endif