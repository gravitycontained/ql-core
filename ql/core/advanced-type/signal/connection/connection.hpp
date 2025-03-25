#pragma once

#include <ql/core/definition/definition.hpp>

#include <ql/core/system/print/print.hpp>

#include <functional>

namespace ql
{
	struct single_connection
	{
		std::function<void()> disconnect;

		single_connection(std::function<void()> disconnect_fn)
			: disconnect(std::move(disconnect_fn)) {}

		single_connection() = default;

		~single_connection()
		{
			if (this->disconnect)
			{
				this->disconnect();
			}
		}
	};

	using connection = std::vector<std::unique_ptr<ql::single_connection>>;
}
