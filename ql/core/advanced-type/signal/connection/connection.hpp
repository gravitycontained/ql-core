#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/system/print/print.hpp>

#include <functional>

namespace ql
{
	struct signal_connection_single
	{
		std::function<void()> disconnect;

		signal_connection_single(std::function<void()> disconnect_fn)
			: disconnect(std::move(disconnect_fn)) {}

		signal_connection_single() = default;

		~signal_connection_single()
		{
			if (this->disconnect)
			{
				this->disconnect();
			}
		}
	};

	using signal_connection = std::vector<std::unique_ptr<ql::signal_connection_single>>;
}
