#pragma once

#include <ql/core/definition/definition.hpp>
#include <ql/core/advanced-type/fundamental/fundamental.hpp>

#if defined QL_GRAPHIC
#include <SFML/Graphics/RenderStates.hpp>
#include <ql/graphic/event/event.hpp>
#endif

namespace ql
{
	class camera
	{
	 public:
		camera()
		{
			this->construct();
		}

		QL_SOURCE ql::vec3 get_view_rotation_coordinates() const;
		QL_SOURCE ql::vec3 get_resulting_looking_position() const;
		QL_SOURCE ql::mat4 get_view() const;
		QL_SOURCE ql::mat4 get_view_projection() const;

		QL_SOURCE void set_position(ql::vec3 pos);
		QL_SOURCE void set_position(ql::f32 x, ql::f32 y, ql::f32 z);
		QL_SOURCE void set_position_x(ql::f32 x);
		QL_SOURCE void set_position_y(ql::f32 y);
		QL_SOURCE void set_position_z(ql::f32 z);
		QL_SOURCE ql::vec3 get_position() const;
		QL_SOURCE ql::f32 get_position_x() const;
		QL_SOURCE ql::f32 get_position_y() const;
		QL_SOURCE ql::f32 get_position_z() const;

		QL_SOURCE void move(ql::vec3 delta);
		QL_SOURCE void move(ql::f32 x, ql::f32 y, ql::f32 z);
		QL_SOURCE void move_x(ql::f32 x);
		QL_SOURCE void move_y(ql::f32 y);
		QL_SOURCE void move_z(ql::f32 z);

		QL_SOURCE void set_aspect(ql::vec2 dimension);
		QL_SOURCE void set_near(ql::f32 value_near);
		QL_SOURCE void set_far(ql::f32 value_far);

		QL_SOURCE void move_forward(ql::f32 delta = 1);
		QL_SOURCE void move_backwards(ql::f32 delta = 1);
		QL_SOURCE void move_left(ql::f32 delta = 1);
		QL_SOURCE void move_right(ql::f32 delta = 1);
		QL_SOURCE void move_up(ql::f32 delta = 1);
		QL_SOURCE void move_down(ql::f32 delta = 1);

		QL_SOURCE void set_view_rotation(ql::vec2 pos);
		QL_SOURCE void set_view_rotation(ql::f32 x, ql::f32 y);
		QL_SOURCE void set_view_rotation_x(ql::f32 x);
		QL_SOURCE void set_view_rotation_y(ql::f32 y);

		QL_SOURCE ql::vec2 get_view_rotation() const;
		QL_SOURCE ql::f32 get_view_rotation_x() const;
		QL_SOURCE ql::f32 get_view_rotation_y() const;

		QL_SOURCE void rotate_view(ql::vec2 delta);

		QL_SOURCE void look_backwards();
		QL_SOURCE void look_up(ql::f32 delta = ql::pi_32 / 2);
		QL_SOURCE void look_down(ql::f32 delta = ql::pi_32 / 2);
		QL_SOURCE void look_left(ql::f32 delta = ql::pi_32 / 2);
		QL_SOURCE void look_right(ql::f32 delta = ql::pi_32 / 2);

		QL_SOURCE void rotate_view_x(ql::f32 x);
		QL_SOURCE void rotate_view_y(ql::f32 x);

		QL_SOURCE void set_max_velocity(ql::f32 max);
		QL_SOURCE ql::f32 get_max_velocity() const;

		QL_SOURCE void set_acceleration(ql::f32 acceleration);
		QL_SOURCE ql::f32 get_acceleration() const;

		QL_SOURCE void set_deacceleration(ql::f32 deacceleration);
		QL_SOURCE ql::f32 get_deacceleration() const;

		QL_SOURCE void accelerate_forwards(ql::f32 delta);
		QL_SOURCE void accelerate_backwards(ql::f32 delta);
		QL_SOURCE void accelerate_left(ql::f32 delta);
		QL_SOURCE void accelerate_right(ql::f32 delta);
		QL_SOURCE void accelerate_up(ql::f32 delta);
		QL_SOURCE void accelerate_down(ql::f32 delta);

		QL_SOURCE void set_speed(ql::f32 speed);
		QL_SOURCE ql::f32 get_speed() const;

		QL_SOURCE void update(ql::f32 delta_time);
		QL_SOURCE void cap_max_velocity();

#if defined QL_GRAPHIC
		QL_SOURCE void update(const ql::event_manager& event);
		QL_SOURCE sf::RenderStates get_render_states() const;
#endif

		QL_SOURCE ql::vec3 get_velocity() const;

		QL_SOURCE void construct();

		ql::mat4 perspective;
		ql::f32 value_near = 1e-3f;
		ql::f32 value_far = 1e3;
		ql::f32 aspect = 16 / 9.0f;
		ql::mat4 model;
		ql::vec2 view_rotation;
		ql::vec3 position;

		ql::vec3 velocities;
		ql::f32 max_velocity;
		ql::f32 accelerate;
		ql::f32 deaccelerate;
		ql::f32 speed;
		ql::f32 mouse_speed = 2.5f;
		bool allow_looking = true;
		bool accelerating = false;
		bool accelerate_in_view_direction = false;
	};
}	 // namespace ql