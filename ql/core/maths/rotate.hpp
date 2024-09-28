#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/advanced-type/fundamental/fundamental.hpp>

namespace ql
{

	template <typename T1, typename T2>
	constexpr auto rotate(T1 angle, const ql::vectorN<T2, 3>& normal)
	{
		using superior = ql::superior_arithmetic_type<T1, T2>;
		return ql::matrixN<superior, 4>(1).rotated(angle, normal);
	}

	template <typename T1, typename T2, typename T3>
	constexpr ql::vec3 rotate(const ql::vectorN<T1, 3>& vec, T2 angle, const ql::vectorN<T3, 3>& normal)
	{
		using superior = ql::superior_arithmetic_type<T1, T2, T3>;
		return ql::matrixN<superior, 3>(ql::rotate(angle, normal)) * vec;
	}

	template <typename T1, typename T2, typename T3>
	constexpr ql::vec3 rotate_towards(const ql::vectorN<T1, 3>& vec, T2 angle, const ql::vectorN<T3, 3>& normal)
	{
		using superior = ql::superior_arithmetic_type<T1, T3>;
		auto up = ql::vectorN<superior, 3>::cross(vec, normal);
		return ql::rotate(vec, angle, up);
	}

	template <typename T1, typename T2>
	constexpr ql::vec3 rotate_x(const ql::vectorN<T1, 3>& vec, T2 angle)
	{
		return ql::rotate_towards(vec, angle, ql::vec(1, 0, 0));
	}

	template <typename T1, typename T2>
	constexpr ql::vec3 rotate_y(const ql::vectorN<T1, 3>& vec, T2 angle)
	{
		return ql::rotate_towards(vec, angle, ql::vec(0, 1, 0));
	}

	template <typename T1, typename T2>
	constexpr ql::vec3 rotate_z(const ql::vectorN<T1, 3>& vec, T2 angle)
	{
		return ql::rotate_towards(vec, angle, ql::vec(0, 0, 1));
	}

}