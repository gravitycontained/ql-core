#include <ql/core/advanced-type/graphic/camera.hpp>
#include <ql/core/maths/circular/circular.hpp>

#include <cmath>
#include <algorithm>

namespace ql
{
	void ql::camera::construct()
	{
		this->position = {0, 0, 0};
		this->view_rotation = {0, 0};
		this->velocities = {0, 0, 0};
		this->max_velocity = 2;
		this->accelerate = 0.2f;
		this->deaccelerate = 5.0f;
		this->speed = 1.0;
		this->accelerating = false;
		this->model = ql::mat4::rotate(ql::mat4(1.0f), 0.0f, {0, 0, 1});
		this->perspective = ql::mat4::perspective(ql::radians(45.0f), this->aspect, this->value_near, this->value_far);

		this->set_deacceleration(10.0f);
		this->set_acceleration(15.0f);
		this->set_max_velocity(3.0f);
		this->set_position({3, 3, 3});
		this->set_view_rotation({-2.5, -0.5});
	}

	ql::vec3 ql::camera::get_view_rotation_coordinates() const
	{
		auto pitch = this->view_rotation.x;
		auto yaw = this->view_rotation.y;

		ql::vec3 result;
		result.x = std::cos(pitch) * std::cos(yaw);
		result.y = std::sin(yaw);
		// result.y = std::sin(pitch);
		result.z = std::sin(pitch) * std::cos(yaw);
		return result;
	}

	ql::vec3 ql::camera::get_resulting_looking_position() const
	{
		return this->position + this->get_view_rotation_coordinates();
	}

	ql::mat4 ql::camera::get_view() const
	{
		ql::vec3 rot = {0, 1, 0};

		auto look = this->get_resulting_looking_position();
		return ql::mat4::look_at(this->position, look, rot);
	}

	ql::mat4 ql::camera::get_view_projection() const
	{
		return this->perspective * this->get_view() * this->model;
	}

	void ql::camera::set_position(ql::vec3 pos)
	{
		this->position = pos;
	}

	void ql::camera::set_position(ql::f32 x, ql::f32 y, ql::f32 z)
	{
		this->set_position({x, y, z});
	}

	void ql::camera::set_position_x(ql::f32 x)
	{
		this->position.x = x;
	}

	void ql::camera::set_position_y(ql::f32 y)
	{
		this->position.y = y;
	}

	void ql::camera::set_position_z(ql::f32 z)
	{
		this->position.z = z;
	}

	ql::vec3 ql::camera::get_position() const
	{
		return this->position;
	}

	ql::f32 ql::camera::get_position_x() const
	{
		return this->position.x;
	}

	ql::f32 ql::camera::get_position_y() const
	{
		return this->position.y;
	}

	ql::f32 ql::camera::get_position_z() const
	{
		return this->position.z;
	}

	void ql::camera::move(ql::vec3 delta)
	{
		this->position += delta;
	}

	void ql::camera::move(ql::f32 x, ql::f32 y, ql::f32 z)
	{
		this->move({x, y, z});
	}

	void ql::camera::move_x(ql::f32 x)
	{
		this->position.x += x;
	}

	void ql::camera::move_y(ql::f32 y)
	{
		this->position.y += y;
	}

	void ql::camera::move_z(ql::f32 z)
	{
		this->position.z += z;
	}

	void ql::camera::set_aspect(ql::vec2 dimension)
	{
		this->aspect = dimension.x / dimension.y;
		this->perspective = ql::mat4::perspective(ql::radians(45.0f), this->aspect, this->value_near, this->value_far);
	}

	void ql::camera::set_near(ql::f32 value_near)
	{
		this->value_near = value_near;
		this->perspective = ql::mat4::perspective(ql::radians(45.0f), this->aspect, this->value_near, this->value_far);
	}

	void ql::camera::set_far(ql::f32 value_far)
	{
		this->value_far = value_far;
		this->perspective = ql::mat4::perspective(ql::radians(45.0f), this->aspect, this->value_near, this->value_far);
	}

	void ql::camera::move_forward(ql::f32 delta)
	{
		auto vec = this->get_view_rotation_coordinates() * delta;
		this->move(vec);
	}

	void ql::camera::move_backwards(ql::f32 delta)
	{
		this->look_backwards();
		auto vec = this->get_view_rotation_coordinates() * delta;
		this->look_backwards();
		this->move(vec);
	}

	void ql::camera::move_up(ql::f32 delta)
	{
		this->look_up();
		auto vec = this->get_view_rotation_coordinates() * delta;
		this->look_down();
		this->move(vec);
	}

	void ql::camera::move_down(ql::f32 delta)
	{
		this->look_down();
		auto vec = this->get_view_rotation_coordinates() * delta;
		this->look_up();
		this->move(vec);
	}

	void ql::camera::move_left(ql::f32 delta)
	{
		this->look_left();
		auto vec = this->get_view_rotation_coordinates() * delta;
		this->look_right();
		this->move(vec);
	}

	void ql::camera::move_right(ql::f32 delta)
	{
		this->look_right();
		auto vec = this->get_view_rotation_coordinates() * delta;
		this->look_left();
		this->move(vec);
	}

	void ql::camera::set_view_rotation(ql::vec2 pos)
	{
		this->set_view_rotation_x(pos.x);
		this->set_view_rotation_y(pos.y);
	}

	void ql::camera::set_view_rotation(ql::f32 x, ql::f32 y)
	{
		this->set_view_rotation_x(x);
		this->set_view_rotation_y(y);
	}

	void ql::camera::set_view_rotation_x(ql::f32 x)
	{
		this->view_rotation.x = x;
	}

	void ql::camera::set_view_rotation_y(ql::f32 y)
	{
		this->view_rotation.y = y;
	}

	ql::vec2 ql::camera::get_view_rotation() const
	{
		return this->view_rotation;
	}

	ql::f32 ql::camera::get_view_rotation_x() const
	{
		return this->view_rotation.x;
	}

	ql::f32 ql::camera::get_view_rotation_y() const
	{
		return this->view_rotation.y;
	}

	void ql::camera::rotate_view(ql::vec2 delta)
	{
		this->set_view_rotation(this->get_view_rotation() + delta);
	}

	void ql::camera::look_backwards()
	{
		this->rotate_view_y(static_cast<ql::f32>(ql::pi));
	}

	void ql::camera::look_up(ql::f32 delta)
	{
		this->rotate_view_y(delta);
	}

	void ql::camera::look_down(ql::f32 delta)
	{
		this->rotate_view_y(-delta);
	}

	void ql::camera::look_left(ql::f32 delta)
	{
		this->rotate_view_x(-delta);
	}

	void ql::camera::look_right(ql::f32 delta)
	{
		this->rotate_view_x(delta);
	}

	void ql::camera::rotate_view_x(ql::f32 x)
	{
		this->set_view_rotation_x(this->view_rotation.x + x);
	}

	void ql::camera::rotate_view_y(ql::f32 y)
	{
		this->set_view_rotation_y(this->view_rotation.y + y);
	}

	void ql::camera::set_max_velocity(ql::f32 max)
	{
		this->max_velocity = max;
	}

	ql::f32 ql::camera::get_max_velocity() const
	{
		return this->max_velocity;
	}

	void ql::camera::set_acceleration(ql::f32 acceleration)
	{
		this->accelerate = acceleration;
	}

	ql::f32 ql::camera::get_acceleration() const
	{
		return this->accelerate;
	}

	void ql::camera::set_deacceleration(ql::f32 deacceleration)
	{
		this->deaccelerate = deacceleration;
	}

	ql::f32 ql::camera::get_deacceleration() const
	{
		return this->deaccelerate;
	}

	void ql::camera::accelerate_forwards(ql::f32 delta)
	{
		auto vec = this->get_view_rotation_coordinates();
		if (!this->accelerate_in_view_direction)
		{
			vec.y = 0;
		}
		this->velocities += vec.normalized() * delta * this->accelerate;
		this->accelerating = true;
	}

	void ql::camera::accelerate_backwards(ql::f32 delta)
	{
		this->look_backwards();
		auto vec = this->get_view_rotation_coordinates();
		this->look_backwards();

		if (!this->accelerate_in_view_direction)
		{
			vec.y = 0;
		}
		this->velocities += vec.normalized() * delta * this->accelerate;
		this->accelerating = true;
	}

	void ql::camera::accelerate_left(ql::f32 delta)
	{
		this->look_left();
		auto vec = this->get_view_rotation_coordinates();
		this->look_right();

		if (!this->accelerate_in_view_direction)
		{
			vec.y = 0;
		}
		auto accel = vec.normalized() * delta * this->accelerate;
		this->velocities += accel;
		this->accelerating = true;
	}

	void ql::camera::accelerate_right(ql::f32 delta)
	{
		this->look_right();
		auto vec = this->get_view_rotation_coordinates();
		this->look_left();

		if (!this->accelerate_in_view_direction)
		{
			vec.y = 0;
		}
		auto accel = vec.normalized() * delta * this->accelerate;
		this->velocities += accel;
		this->accelerating = true;
	}

	void ql::camera::accelerate_up(ql::f32 delta)
	{
		this->velocities.y += delta * this->accelerate;
		this->accelerating = true;
	}

	void ql::camera::accelerate_down(ql::f32 delta)
	{
		this->velocities.y -= delta * this->accelerate;
		this->accelerating = true;
	}

	void ql::camera::set_speed(ql::f32 speed)
	{
		this->speed = speed;
	}

	ql::f32 ql::camera::get_speed() const
	{
		return this->speed;
	}

	void ql::camera::cap_max_velocity()
	{
		if (this->velocities.length() > this->max_velocity)
		{
			this->velocities = this->velocities.normalized() * this->max_velocity;
		}
	}

	void ql::camera::update(ql::f32 delta_time)
	{
		this->cap_max_velocity();

		if (!this->accelerating)
		{
			auto n = delta_time * this->deaccelerate;
			auto deaccel = std::pow(0.5, n);

			this->velocities *= deaccel;
		}

		this->position += this->velocities * delta_time * this->speed;

		this->view_rotation.x = static_cast<ql::f32>(std::fmod(this->view_rotation.x, ql::pi * 2));
		this->view_rotation.y = static_cast<ql::f32>(std::fmod(this->view_rotation.y + ql::pi_32 / 2, ql::pi * 2)) - ql::pi_32 / 2;

		this->view_rotation.y = std::max(this->view_rotation.y, -ql::pi_32 / 2 + 0.01f);
		this->view_rotation.y = std::min(this->view_rotation.y, ql::pi_32 / 2 - 0.01f);
	}

#if defined ql_INTERN_SFML_USE

	void ql::camera::update(const ql::event_info& event)
	{
		if (this->allow_looking)
		{
			auto delta = event.delta_mouse_position() / event.screen_dimension();
			this->look_right(delta.x * this->mouse_speed);
			this->look_down(delta.y * this->mouse_speed);
		}
		auto delta_time = ql::f32_cast(event.frame_time_f());

		bool up = event.key_holding(sf::Keyboard::Key::Space);
		bool down = event.key_holding(sf::Keyboard::Key::LShift);
		bool left = event.key_holding(sf::Keyboard::Key::A);
		bool right = event.key_holding(sf::Keyboard::Key::D);
		bool forwards = event.key_holding(sf::Keyboard::Key::W);
		bool backwards = event.key_holding(sf::Keyboard::Key::S);

		this->accelerating = false;
		if (up)
			this->accelerate_up(delta_time);
		if (down)
			this->accelerate_down(delta_time);
		if (left)
			this->accelerate_left(delta_time);
		if (right)
			this->accelerate_right(delta_time);
		if (forwards)
			this->accelerate_forwards(delta_time);
		if (backwards)
			this->accelerate_backwards(delta_time);

		this->accelerating = left || right || up || down || forwards || backwards;

		this->update(delta_time);

		if (event.resized())
		{
			this->set_aspect(event.screen_dimension());
		}
	}

	sf::RenderStates ql::camera::get_render_states() const
	{
		sf::RenderStates states;
		states.transform;

		auto proj = this->get_view_projection();
		memcpy(&states.transform, &proj, sizeof(states.transform));
		return states;
	}

#endif

	ql::vec3 ql::camera::get_velocity() const
	{
		return this->velocities;
	}
}	 // namespace ql