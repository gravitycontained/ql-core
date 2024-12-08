#pragma once

#include <ql/core/definition/definition.hpp>

namespace ql
{
	namespace detail
	{
		template <ql::size>
		struct anything
		{
			template <class T>
			operator T() const;
		};
		template <class T, ql::size... Ints>
		concept is_constructible_c = requires { T{anything<Ints>{}...}; };
	}	 // namespace detail

	template <class T, ql::size N = 0u>
	constexpr auto is_constructible()
	{
		constexpr auto unpack = [&]<qpl::size... Ints>(std::index_sequence<Ints...>)
		{ return qpl::detail::is_constructible_c<T, Ints...>; };
		return unpack(std::make_index_sequence<N>{});
	}

	namespace detail
	{
		template <class T, ql::size N = 0u, bool found = false>
		constexpr auto find_struct_members_count()
		{
			constexpr auto constructible = ql::is_constructible<T, N>();

			if constexpr (found && !constructible)
			{
				return N - 1;
			}
			else if constexpr (constructible)
			{
				return find_struct_members_count<T, N + 1, true>();
			}
			else
			{
				return find_struct_members_count<T, N + 1, found>();
			}
		}
	}	 // namespace detail

	template <typename T>
	constexpr auto get_struct_members_count()
	{
		return ql::detail::find_struct_members_count<T>();
	}

	namespace detail
	{
		template <class T, ql::size N>
		constexpr auto get_struct_members_tuple(T& n)
		{
			if constexpr (N == 0)
				return std::tuple<>{};
			else if constexpr (N == 1)
			{
				auto& [v0] = n;
				return std::tie(v0);
			}
			else if constexpr (N == 2)
			{
				auto& [v0, v1] = n;
				return std::tie(v0, v1);
			}
			else if constexpr (N == 3)
			{
				auto& [v0, v1, v2] = n;
				return std::tie(v0, v1, v2);
			}
			else if constexpr (N == 4)
			{
				auto& [v0, v1, v2, v3] = n;
				return std::tie(v0, v1, v2, v3);
			}
			else if constexpr (N == 5)
			{
				auto& [v0, v1, v2, v3, v4] = n;
				return std::tie(v0, v1, v2, v3, v4);
			}
			else if constexpr (N == 6)
			{
				auto& [v0, v1, v2, v3, v4, v5] = n;
				return std::tie(v0, v1, v2, v3, v4, v5);
			}
			else if constexpr (N == 7)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6] = n;
				return std::tie(v0, v1, v2, v3, v4, v5, v6);
			}
			else if constexpr (N == 8)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7] = n;
				return std::tie(v0, v1, v2, v3, v4, v5, v6, v7);
			}
			else if constexpr (N == 9)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8] = n;
				return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8);
			}
			else if constexpr (N == 10)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9] = n;
				return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
			}
			else if constexpr (N == 11)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va] = n;
				return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va);
			}
			else if constexpr (N == 12)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb] = n;
				return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb);
			}
			else if constexpr (N == 13)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc] = n;
				return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc);
			}
			else if constexpr (N == 14)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd] = n;
				return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd);
			}
			else if constexpr (N == 15)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve] = n;
				return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve);
			}
			else if constexpr (N == 16)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf] = n;
				return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf);
			}
			else if constexpr (N == 17)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg] = n;
				return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg);
			}
			else if constexpr (N == 18)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh] = n;
				return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh);
			}
			else if constexpr (N == 19)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi] = n;
				return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi);
			}
			else if constexpr (N == 20)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj] = n;
				return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj);
			}
			else if constexpr (N == 21)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk] = n;
				return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk);
			}
			else if constexpr (N == 22)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl] = n;
				return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl);
			}
			else if constexpr (N == 23)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm] = n;
				return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm);
			}
			else if constexpr (N == 24)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn] = n;
				return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn);
			}
			else if constexpr (N == 25)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo] = n;
				return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo);
			}
			else if constexpr (N == 26)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp] = n;
				return std::tie(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp);
			}
			else if constexpr (N == 27)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq] = n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq
				);
			}
			else if constexpr (N == 28)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr
				);
			}
			else if constexpr (N == 29)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs
				);
			}
			else if constexpr (N == 30)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt
				);
			}
			else if constexpr (N == 31)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu
				);
			}
			else if constexpr (N == 32)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv
				);
			}
			else if constexpr (N == 33)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw
				);
			}
			else if constexpr (N == 34)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx
				);
			}
			else if constexpr (N == 35)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy
				);
			}
			else if constexpr (N == 36)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz
				);
			}
			else if constexpr (N == 37)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10
				);
			}
			else if constexpr (N == 38)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11
				);
			}
			else if constexpr (N == 39)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12
				);
			}
			else if constexpr (N == 40)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13
				);
			}
			else if constexpr (N == 41)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14
				);
			}
			else if constexpr (N == 42)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15
				);
			}
			else if constexpr (N == 43)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16
				);
			}
			else if constexpr (N == 44)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17
				);
			}
			else if constexpr (N == 45)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18
				);
			}
			else if constexpr (N == 46)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19
				);
			}
			else if constexpr (N == 47)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a
				);
			}
			else if constexpr (N == 48)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b
				);
			}
			else if constexpr (N == 49)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c
				);
			}
			else if constexpr (N == 50)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d
				);
			}
			else if constexpr (N == 51)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e
				);
			}
			else if constexpr (N == 52)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f
				);
			}
			else if constexpr (N == 53)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g
				);
			}
			else if constexpr (N == 54)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h
				);
			}
			else if constexpr (N == 55)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i
				);
			}
			else if constexpr (N == 56)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j
				);
			}
			else if constexpr (N == 57)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k
				);
			}
			else if constexpr (N == 58)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l
				);
			}
			else if constexpr (N == 59)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m
				);
			}
			else if constexpr (N == 60)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n
				);
			}
			else if constexpr (N == 61)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o
				);
			}
			else if constexpr (N == 62)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p
				);
			}
			else if constexpr (N == 63)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q
				);
			}
			else if constexpr (N == 64)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r
				);
			}
			else if constexpr (N == 65)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s
				);
			}
			else if constexpr (N == 66)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t
				);
			}
			else if constexpr (N == 67)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u
				);
			}
			else if constexpr (N == 68)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v
				);
			}
			else if constexpr (N == 69)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w
				);
			}
			else if constexpr (N == 70)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x
				);
			}
			else if constexpr (N == 71)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y
				);
			}
			else if constexpr (N == 72)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z
				);
			}
			else if constexpr (N == 73)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20
				);
			}
			else if constexpr (N == 74)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21
				);
			}
			else if constexpr (N == 75)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22
				);
			}
			else if constexpr (N == 76)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23
				);
			}
			else if constexpr (N == 77)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24
				);
			}
			else if constexpr (N == 78)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25
				);
			}
			else if constexpr (N == 79)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26
				);
			}
			else if constexpr (N == 80)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27
				);
			}
			else if constexpr (N == 81)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28
				);
			}
			else if constexpr (N == 82)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29
				);
			}
			else if constexpr (N == 83)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a
				);
			}
			else if constexpr (N == 84)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b
				);
			}
			else if constexpr (N == 85)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c
				);
			}
			else if constexpr (N == 86)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d
				);
			}
			else if constexpr (N == 87)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e
				);
			}
			else if constexpr (N == 88)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f
				);
			}
			else if constexpr (N == 89)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g
				);
			}
			else if constexpr (N == 90)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h
				);
			}
			else if constexpr (N == 91)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i
				);
			}
			else if constexpr (N == 92)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j
				);
			}
			else if constexpr (N == 93)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k
				);
			}
			else if constexpr (N == 94)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l
				);
			}
			else if constexpr (N == 95)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m
				);
			}
			else if constexpr (N == 96)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n
				);
			}
			else if constexpr (N == 97)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o
				);
			}
			else if constexpr (N == 98)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p
				);
			}
			else if constexpr (N == 99)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q
				);
			}
			else if constexpr (N == 100)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r
				);
			}
			else if constexpr (N == 101)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s
				);
			}
			else if constexpr (N == 102)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t
				);
			}
			else if constexpr (N == 103)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u
				);
			}
			else if constexpr (N == 104)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v
				);
			}
			else if constexpr (N == 105)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w
				);
			}
			else if constexpr (N == 106)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x
				);
			}
			else if constexpr (N == 107)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y
				);
			}
			else if constexpr (N == 108)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z
				);
			}
			else if constexpr (N == 109)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30
				);
			}
			else if constexpr (N == 110)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31
				);
			}
			else if constexpr (N == 111)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32
				);
			}
			else if constexpr (N == 112)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33
				);
			}
			else if constexpr (N == 113)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34
				);
			}
			else if constexpr (N == 114)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35
				);
			}
			else if constexpr (N == 115)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36
				);
			}
			else if constexpr (N == 116)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37
				);
			}
			else if constexpr (N == 117)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38
				);
			}
			else if constexpr (N == 118)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39
				);
			}
			else if constexpr (N == 119)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v3a] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v3a
				);
			}
			else if constexpr (N == 120)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v3a, v3b] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v3a, v3b
				);
			}
			else if constexpr (N == 121)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v3a, v3b, v3c] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v3a, v3b, v3c
				);
			}
			else if constexpr (N == 122)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v3a, v3b, v3c, v3d] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v3a, v3b, v3c, v3d
				);
			}
			else if constexpr (N == 123)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v3a, v3b, v3c, v3d, v3e] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v3a, v3b, v3c, v3d, v3e
				);
			}
			else if constexpr (N == 124)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v3a, v3b, v3c, v3d, v3e, v3f] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v3a, v3b, v3c, v3d, v3e, v3f
				);
			}
			else if constexpr (N == 125)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v3a, v3b, v3c, v3d, v3e, v3f, v3g] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v3a, v3b, v3c, v3d, v3e,
						v3f, v3g
				);
			}
			else if constexpr (N == 126)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v3a, v3b, v3c, v3d, v3e, v3f, v3g, v3h] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v3a, v3b, v3c, v3d, v3e,
						v3f, v3g, v3h
				);
			}
			else if constexpr (N == 127)
			{
				auto& [v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs, vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h, v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24, v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r, v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v3a, v3b, v3c, v3d, v3e, v3f, v3g, v3h, v3i] =
						n;
				return std::tie(
						v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl, vm, vn, vo, vp, vq, vr, vs,
						vt, vu, vv, vw, vx, vy, vz, v10, v11, v12, v13, v14, v15, v16, v17, v18, v19, v1a, v1b, v1c, v1d, v1e, v1f, v1g, v1h,
						v1i, v1j, v1k, v1l, v1m, v1n, v1o, v1p, v1q, v1r, v1s, v1t, v1u, v1v, v1w, v1x, v1y, v1z, v20, v21, v22, v23, v24,
						v25, v26, v27, v28, v29, v2a, v2b, v2c, v2d, v2e, v2f, v2g, v2h, v2i, v2j, v2k, v2l, v2m, v2n, v2o, v2p, v2q, v2r,
						v2s, v2t, v2u, v2v, v2w, v2x, v2y, v2z, v30, v31, v32, v33, v34, v35, v36, v37, v38, v39, v3a, v3b, v3c, v3d, v3e,
						v3f, v3g, v3h, v3i
				);
			}
			else
			{
				static_assert("struct member size too large.");
			}
		}
	}	 // namespace detail

	template <typename T>
	constexpr auto get_struct_members_tuple(T& value)
	{
		return ql::detail::get_struct_members_tuple<T, ql::get_struct_members_count<T>()>(value);
	}
}