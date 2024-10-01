#pragma once

#include <ql/core/definition/definition.hpp>
#if defined QL_SFML

#include <ql/core/advanced-type/fundamental/vector.hpp>
#include <ql/core/advanced-type/graphic/hitbox.hpp>
#include <SFML/Graphics.hpp>

namespace ql
{
	template <bool opengl>
	struct draw_object_t;
	using draw_object = draw_object_t<false>;
	using draw_object_gl = draw_object_t<true>;

	template <typename T>
	struct view_t
	{
		ql::vector2<T> position = {T{0}, T{0}};
		ql::vector2<T> scale = {T{1}, T{1}};
		T rotation = T{0};

		sf::Transform get_transform() const
		{
			sf::Transform transform;
			transform.rotate(ql::f32_cast(this->rotation)).scale(1 / ql::vec2(this->scale)).translate(-ql::vec2(this->position));
			// transform.rotate(ql::f32_cast(this->rotation)).scale(ql:vec2(this->scale)).translate(ql:vec2(this->position));
			return transform;
		}

		sf::Transform get_transform_no_offset() const
		{
			sf::Transform transform;
			transform.rotate(ql::f32_cast(this->rotation)).scale(1 / ql::vec2(this->scale));
			// transform.rotate(ql::f32_cast(this->rotation)).scale(ql:vec2(this->scale));
			return transform;
		}

		sf::RenderStates get_render_states() const
		{
			sf::RenderStates states;
			states.transform = this->get_transform();
			return states;
		}

		ql::vec2f transform_point(ql::vec2f position) const
		{
			auto transform = this->get_transform().getInverse();
			// auto transform = this->get_transform();
			return transform.transformPoint(position);
		}

		ql::vec2f transform_point_no_offset(ql::vec2f position) const
		{
			auto transform = this->get_transform_no_offset().getInverse();
			// auto transform = this->get_transform_no_offset();
			return transform.transformPoint(position);
		}

		ql::hitbox transform_hitbox(ql::hitbox hitbox) const
		{
			hitbox.position = this->transform_point(hitbox.position);
			hitbox.dimension = this->transform_point_no_offset(hitbox.dimension);
			return hitbox;
		}

		constexpr void reset()
		{
			this->position = {T{0}, T{0}};
			this->scale = {T{1}, T{1}};
			this->rotation = T{0};
		}

		constexpr void set_rotation(T rotation)
		{
			this->rotation = rotation;
		}

		constexpr void move(ql::vector2<T> delta)
		{
			this->position.move(delta);
		}

		constexpr void set_position(ql::vector2<T> position)
		{
			this->position = position;
		}

		constexpr void set_scale(ql::vector2<T> scale)
		{
			this->scale = scale;
		}

		constexpr bool is_default_view() const
		{
			return this->position == ql::vector2<T>{T{0}, T{0}} && this->scale == ql::vector2<T>{T{1}, T{1}} && this->rotation == T{0};
		}

		constexpr T get_rotation() const
		{
			return this->rotation;
		}

		constexpr ql::vector2<T> get_position() const
		{
			return this->position;
		}

		constexpr ql::vector2<T> get_scale() const
		{
			return this->scale;
		}

		constexpr void apply_to(sf::RenderStates& states) const
		{
			this->apply_to(states.transform);
		}

		constexpr void apply_to(sf::Transform& transform) const
		{
			transform.combine(this->get_transform());
		}

		constexpr void apply_to_inverse(sf::RenderStates& states) const
		{
			this->apply_to_inverse(states.transform);
		}

		constexpr void apply_to_inverse(sf::Transform& transform) const
		{
			transform.combine(this->get_transform().getInverse());
		}
	};

	using view = ql::view_t<ql::f32>;

	template <typename T>
	struct view_extension : T
	{
		ql::view view;
	};

	namespace detail
	{
		template <typename T>
		constexpr auto view_signature(ql::view_t<T>)
		{
			return std::true_type{};
		}

		template <typename T>
		constexpr auto view_signature(T)
		{
			return std::false_type{};
		}
	}	 // namespace detail

	template <typename T>
	constexpr bool is_view()
	{
		return decltype(ql::detail::view_signature(ql::declval<T>())){};
	}

	template <typename T>
	concept has_view_c = requires(T x) {
		{ x.auto_view };
		requires ql::is_view<decltype(T::auto_view)>();
	};

	template <typename T>
	constexpr bool has_view()
	{
		return has_view_c<T>;
	}
}	 // namespace ql

#endif