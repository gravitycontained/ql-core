#pragma once

#include <functional>

namespace ql
{
	template <typename T>
	using reference = std::reference_wrapper<T>;
}