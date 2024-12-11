#pragma once

#include <ql/core/definition/definition.hpp>

#if defined QL_GRAPHIC

#include <ql/graphic/drawable/drawable.hpp>

#include <ql/core/type/type.hpp>
#include <ql/core/advanced-type/advanced-type.hpp>
#include <ql/core/system/exception/exception.hpp>
#include <ql/core/transform/container/fill.hpp>

#include <ql/graphic/render/render.hpp>

#include <functional>
#include <string>
#include <unordered_map>
#include <type_traits>
#include <cwctype>
#include <span>

#include <SFML/Graphics.hpp>

namespace ql
{

	struct vtext;
	struct text;
	struct vrectangle;
	struct rectangle;
	struct vrectangles;
	struct rectangles;
	struct vsmooth_corner;
	struct smooth_corner;
	struct vpoint;
	struct point;
	struct vpoints;
	struct points;
	struct vcircle;
	struct circle_shape;
	struct vcircles;
	struct circles;
	struct vline;
	struct line;
	struct vlines;
	struct lines;
	struct vthick_line;
	struct thick_line;
	struct vthick_lines;
	struct thick_lines;
	struct vgraph;
	struct graph;

	struct event;

	namespace detail
	{
		QL_SOURCE extern ql::rectangle rectangle;
		QL_SOURCE extern ql::rectangles rectangles;
		QL_SOURCE extern ql::smooth_corner smooth_corner;
		QL_SOURCE extern ql::point point;
		QL_SOURCE extern ql::points points;
		QL_SOURCE extern ql::circle_shape circle;
		QL_SOURCE extern ql::circles circles;
		QL_SOURCE extern ql::line line;
		QL_SOURCE extern ql::lines lines;
		QL_SOURCE extern ql::thick_line thick_line;
		QL_SOURCE extern ql::thick_lines thick_lines;
		QL_SOURCE extern ql::graph graph;
	}	 // namespace detail

	QL_SOURCE extern ql::vgraph drawing_graph;

	struct vertex
	{
		vertex()
		{
		}

		vertex(ql::vec2 position, ql::rgba color)
		{
			this->position = position;
			this->color = color;
		}

		vertex(ql::vec2 position, ql::rgba color, ql::vec2 tex_coords)
		{
			this->position = position;
			this->color = color;
			this->tex_coords = tex_coords;
		}

		ql::vec2 position;
		ql::rgba color;
		ql::vec2 tex_coords;

		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
	};

	enum class primitive_type
	{
		points,
		lines,
		line_strip,
		triangles,
		triangle_strip,
		triangle_fan,
		quads,
	};

	struct vertex_array
	{
		vertex_array()
		{
		}

		vertex_array(sf::PrimitiveType primitive_type)
		{
			this->set_primitive_type(primitive_type);
		}

		QL_SOURCE void set_primitive_type(ql::primitive_type primitive_type);
		QL_SOURCE void set_primitive_type(sf::PrimitiveType primitive_type);

		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void move(ql::vec2 delta);

		QL_SOURCE ql::size size() const;
		QL_SOURCE bool empty() const;
		QL_SOURCE void resize(ql::size new_size);
		QL_SOURCE void reserve(ql::size new_size);

		QL_SOURCE void add(const ql::vertex& vertex);

		QL_SOURCE void clear();

		QL_SOURCE ql::vertex& operator[](ql::size index);
		QL_SOURCE const ql::vertex& operator[](ql::size index) const;

		QL_SOURCE ql::vertex& front();
		QL_SOURCE const ql::vertex& front() const;

		QL_SOURCE ql::vertex& back();
		QL_SOURCE const ql::vertex& back() const;

		QL_SOURCE std::vector<ql::vertex>::iterator begin();
		QL_SOURCE std::vector<ql::vertex>::const_iterator begin() const;
		QL_SOURCE std::vector<ql::vertex>::const_iterator cbegin() const;

		QL_SOURCE std::vector<ql::vertex>::iterator end();
		QL_SOURCE std::vector<ql::vertex>::const_iterator end() const;
		QL_SOURCE std::vector<ql::vertex>::const_iterator cend() const;

		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		std::vector<ql::vertex> vertices;
		ql::primitive_type primitive_type = ql::primitive_type::points;
	};

	struct endl_type
	{
	};

	QL_SOURCE extern endl_type endl;

	struct vrectangle
	{
		vrectangle()
		{
		}

		vrectangle(ql::vec2 position, ql::vec2 dimension)
		{
			this->position = position;
			this->dimension = dimension;
		}

		vrectangle(ql::vec2 position, ql::vec2 dimension, ql::rgba color)
		{
			this->position = position;
			this->dimension = dimension;
			this->color = color;
		}

		vrectangle(ql::hitbox hitbox)
		{
			this->set_position(hitbox.position);
			this->set_dimension(hitbox.dimension);
		}

		QL_SOURCE void set_dimension(ql::vec2 dimension);
		QL_SOURCE void set_position(ql::vec2 position);
		QL_SOURCE void set_center(ql::vec2 position);
		QL_SOURCE void set_hitbox(const ql::hitbox& hitbox);
		QL_SOURCE void set_outline_thickness(ql::f32 outline_thickness);
		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void set_outline_color(ql::rgba outline_color);

		QL_SOURCE ql::vec2 get_dimension() const;
		QL_SOURCE ql::vec2 get_position() const;
		QL_SOURCE ql::vec2 get_center() const;
		QL_SOURCE ql::hitbox get_hitbox() const;
		QL_SOURCE ql::rgba get_color() const;
		QL_SOURCE ql::f32 get_outline_thickness() const;
		QL_SOURCE ql::rgba get_outline_color() const;

		QL_SOURCE std::string string() const;

		QL_SOURCE void increase(ql::f32 delta);
		QL_SOURCE ql::vrectangle increased(ql::f32 delta) const;

		QL_SOURCE bool collides(ql::vec2 position) const;
		QL_SOURCE bool collides(ql::vec2 position, ql::f32 hitbox_increase) const;
		QL_SOURCE bool collides(ql::straight_line line) const;
		QL_SOURCE bool collides(ql::straight_line line, ql::f32 hitbox_increase) const;

		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		ql::vec2 dimension;
		ql::vec2 position;
		ql::f32 outline_thickness = 0.0f;
		ql::rgba color;
		ql::rgba outline_color;
	};

	struct rectangle
	{
		rectangle()
		{
		}

		rectangle(ql::hitbox hitbox)
		{
			this->set_hitbox(hitbox);
		}

		QL_SOURCE void set_dimension(ql::vec2 dimension);
		QL_SOURCE void set_position(ql::vec2 position);
		QL_SOURCE void set_center(ql::vec2 position);
		QL_SOURCE void set_hitbox(const ql::hitbox& hitbox);
		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void set_outline_thickness(ql::f32 outline_thickness);
		QL_SOURCE void set_outline_color(ql::rgba outline_color);

		QL_SOURCE void increase(ql::f64 delta);

		QL_SOURCE ql::rgba get_color() const;
		QL_SOURCE ql::rgba get_outline_color() const;
		QL_SOURCE ql::vec2 get_position() const;
		QL_SOURCE ql::vec2 get_dimension() const;
		QL_SOURCE ql::vec2 get_center() const;
		QL_SOURCE ql::f32 get_outline_thickness() const;
		QL_SOURCE ql::hitbox get_hitbox() const;

		QL_SOURCE ql::vlines as_lines() const;
		QL_SOURCE ql::vlines as_lines_completed() const;

		QL_SOURCE ql::vec2 center() const;
		QL_SOURCE void move(ql::vec2 delta);

		QL_SOURCE ql::rectangle& operator=(const ql::vrectangle& rectangle);

		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		sf::RectangleShape m_rect;
	};

	struct va_rectangle
	{
		va_rectangle()
		{
			this->va.resize(4u);
			this->va.set_primitive_type(ql::primitive_type::quads);
		}

		QL_SOURCE void move(ql::vec2 delta);
		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void set_position(ql::vec2 position);
		QL_SOURCE void set_dimension(ql::vec2 dimension);
		QL_SOURCE void set_hitbox(const ql::hitbox& hitbox);

		ql::vertex& top_left();
		ql::vertex& top_right();
		ql::vertex& bottom_left();
		ql::vertex& bottom_right();

		const ql::vertex& top_left() const;
		const ql::vertex& top_right() const;
		const ql::vertex& bottom_left() const;
		const ql::vertex& bottom_right() const;

		QL_SOURCE ql::vec2 get_position() const;
		QL_SOURCE ql::vec2 get_dimension() const;
		QL_SOURCE ql::hitbox get_hitbox() const;

		ql::vertex_array va;
		ql::hitbox hitbox;

		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QL_SOURCE void apply_hitbox();
	};

	struct vrectangles
	{
		QL_SOURCE ql::size size() const;
		QL_SOURCE void resize(ql::size new_size);
		QL_SOURCE void reserve(ql::size new_size);
		QL_SOURCE void clear();
		QL_SOURCE void add(const ql::vrectangle& rect);

		QL_SOURCE ql::vrectangle& operator[](ql::size index);
		QL_SOURCE const ql::vrectangle& operator[](ql::size index) const;

		QL_SOURCE ql::vrectangle& front();
		QL_SOURCE const ql::vrectangle& front() const;

		QL_SOURCE ql::vrectangle& back();
		QL_SOURCE const ql::vrectangle& back() const;

		QL_SOURCE std::vector<ql::vrectangle>::iterator begin();
		QL_SOURCE std::vector<ql::vrectangle>::const_iterator begin() const;
		QL_SOURCE std::vector<ql::vrectangle>::const_iterator cbegin() const;

		QL_SOURCE std::vector<ql::vrectangle>::iterator end();
		QL_SOURCE std::vector<ql::vrectangle>::const_iterator end() const;
		QL_SOURCE std::vector<ql::vrectangle>::const_iterator cend() const;

		QL_SOURCE void add_rectangle(vrectangle rectangle);
		QL_SOURCE void add_rectangle(ql::vec2 position, ql::vec2 dimension);
		QL_SOURCE void add_rectangle(ql::vec2 position, ql::vec2 dimension, ql::rgba color);

		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QL_SOURCE ql::vrectangles& operator=(const ql::vrectangles& rectangles);

		std::vector<ql::vrectangle> rectangles;
	};

	struct rectangles
	{
		QL_SOURCE ql::size size() const;
		QL_SOURCE void resize(ql::size new_size);
		QL_SOURCE void reserve(ql::size new_size);
		QL_SOURCE void clear();
		QL_SOURCE void add(const ql::rectangle& rect);

		QL_SOURCE ql::rectangle& operator[](ql::size index);
		QL_SOURCE const ql::rectangle& operator[](ql::size index) const;

		QL_SOURCE ql::rectangle& front();
		QL_SOURCE const ql::rectangle& front() const;

		QL_SOURCE ql::rectangle& back();
		QL_SOURCE const ql::rectangle& back() const;

		QL_SOURCE std::vector<ql::rectangle>::iterator begin();
		QL_SOURCE std::vector<ql::rectangle>::const_iterator begin() const;
		QL_SOURCE std::vector<ql::rectangle>::const_iterator cbegin() const;

		QL_SOURCE std::vector<ql::rectangle>::iterator end();
		QL_SOURCE std::vector<ql::rectangle>::const_iterator end() const;
		QL_SOURCE std::vector<ql::rectangle>::const_iterator cend() const;

		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QL_SOURCE ql::rectangles& operator=(const ql::vrectangles& rectangles);

		std::vector<ql::rectangle> rectangles_;
	};

	struct vsmooth_corner
	{
		QL_SOURCE void move(ql::vec2 delta);

		QL_SOURCE void invert();
		QL_SOURCE void set_rotation(ql::f64 rotation);
		QL_SOURCE void set_dimension(ql::vec2 dimension);
		QL_SOURCE void set_position(ql::vec2 position);
		QL_SOURCE void set_hitbox(ql::hitbox hitbox);
		QL_SOURCE void set_center(ql::vec2 position);
		QL_SOURCE void set_slope(ql::f64 slope);
		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void set_slope_point_count(ql::size point_count);
		QL_SOURCE ql::f64 get_rotation() const;
		QL_SOURCE ql::vec2 get_dimension() const;
		QL_SOURCE ql::vec2 get_position() const;
		QL_SOURCE ql::vec2 get_center() const;
		QL_SOURCE ql::hitbox get_hitbox() const;
		QL_SOURCE ql::f64 get_slope() const;
		QL_SOURCE ql::rgba get_color() const;
		QL_SOURCE ql::size get_slope_point_count() const;
		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		friend smooth_corner;

		ql::vec2 dimension;
		ql::vec2 position;
		ql::f64 slope = 2.0;
		ql::size slope_point_count = 30u;
		ql::rgba color;
		ql::f64 rotation = 0.0;
	};

	struct smooth_corner
	{
		mutable ql::vertex_array polygon;

		smooth_corner()
		{
			this->polygon.set_primitive_type(sf::PrimitiveType::TriangleFan);
		}

		QL_SOURCE void invert();
		QL_SOURCE void set_rotation(ql::f64 rotation);
		QL_SOURCE void set_position(ql::vec2 position);
		QL_SOURCE void set_dimension(ql::vec2 dimension);
		QL_SOURCE void set_hitbox(ql::hitbox hitbox);
		QL_SOURCE void set_center(ql::vec2 position);
		QL_SOURCE void set_slope(ql::f64 slope);
		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void set_slope_point_count(ql::size point_count);
		QL_SOURCE ql::f64 get_rotation() const;
		QL_SOURCE ql::vec2 get_dimension() const;
		QL_SOURCE ql::vec2 get_position() const;
		QL_SOURCE ql::hitbox get_hitbox() const;
		QL_SOURCE ql::vec2 get_center() const;
		QL_SOURCE ql::f64 get_slope() const;
		QL_SOURCE ql::rgba get_color() const;
		QL_SOURCE ql::size get_slope_point_count() const;

		QL_SOURCE void check_create() const;
		QL_SOURCE void move(ql::vec2 delta);
		QL_SOURCE const ql::smooth_corner& operator=(const ql::vsmooth_corner& smooth_corner) const;
		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		mutable ql::vec2 dimension;
		mutable ql::vec2 position;
		ql::f64 slope = 2.0;
		ql::size slope_point_count = 30u;
		ql::f64 rotation = 0.0;
		ql::rgb color;
		mutable bool internal_check = false;
	};

	struct vpoint
	{
		ql::vec2 position;
		ql::rgba color;

		vpoint()
		{
		}

		vpoint(ql::vec2 position, ql::rgba color)
		{
			this->position = position;
			this->color = color;
		}

		vpoint(ql::vec2 position)
		{
			this->position = position;
		}

		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QL_SOURCE vpoint& operator=(ql::vec2 position);

		QL_SOURCE bool operator==(const vpoint& other) const;
		QL_SOURCE bool operator!=(const vpoint& other) const;
	};

	struct point
	{
		ql::vertex vertex;

		QL_SOURCE ql::point& operator=(const ql::vpoint& point);
		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
	};

	struct vpoints
	{
		vpoints(ql::size size = ql::size{})
		{
			this->points.resize(size);
		}

		QL_SOURCE ql::size size() const;
		QL_SOURCE void resize(ql::size new_size);
		QL_SOURCE void reserve(ql::size new_size);

		QL_SOURCE ql::vpoint& operator[](ql::size index);
		QL_SOURCE const ql::vpoint& operator[](ql::size index) const;

		QL_SOURCE ql::vpoint& front();
		QL_SOURCE const ql::vpoint& front() const;

		QL_SOURCE ql::vpoint& back();
		QL_SOURCE const ql::vpoint& back() const;

		QL_SOURCE std::vector<ql::vpoint>::iterator begin();
		QL_SOURCE std::vector<ql::vpoint>::const_iterator begin() const;
		QL_SOURCE std::vector<ql::vpoint>::const_iterator cbegin() const;

		QL_SOURCE std::vector<ql::vpoint>::iterator end();
		QL_SOURCE std::vector<ql::vpoint>::const_iterator end() const;
		QL_SOURCE std::vector<ql::vpoint>::const_iterator cend() const;

		QL_SOURCE void add_point(ql::vpoint point);
		QL_SOURCE void add_point(ql::vec2 position, ql::rgba color);
		QL_SOURCE ql::vlines as_lines() const;

		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QL_SOURCE void clear();

		std::vector<ql::vpoint> points;
	};

	struct points
	{
		points()
		{
			this->vertices.set_primitive_type(ql::primitive_type::points);
		}

		points(ql::size size)
		{
			this->vertices.resize(size);
		}

		QL_SOURCE void resize(ql::size new_size);
		QL_SOURCE void reserve(ql::size new_size);

		QL_SOURCE ql::vertex& operator[](ql::size index);
		QL_SOURCE const ql::vertex& operator[](ql::size index) const;

		QL_SOURCE ql::vertex& front();
		QL_SOURCE const ql::vertex& front() const;

		QL_SOURCE ql::vertex& back();
		QL_SOURCE const ql::vertex& back() const;

		QL_SOURCE ql::vlines as_lines() const;
		QL_SOURCE ql::points& operator=(const ql::vpoints& points);
		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QL_SOURCE void clear();
		QL_SOURCE ql::size size() const;
		ql::vertex_array vertices;
	};

	struct vcircle
	{
		vcircle()
		{
			this->radius = 0.0f;
		}

		vcircle(ql::vpoint point, ql::f32 radius)
		{
			this->point = point;
			this->radius = radius;
			this->point.position.move(ql::vec2{-this->radius, -this->radius});
		}

		vcircle(ql::vec2 center, ql::f32 radius, ql::rgba color)
		{
			this->point.position = center - ql::vec2{radius, radius};
			this->point.color = color;
			this->radius = radius;
		}

		QL_SOURCE bool contains(ql::vec2 position) const;
		QL_SOURCE void set_position(ql::vec2 center);
		QL_SOURCE void set_radius(ql::f32 radius);
		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void set_center(ql::vec2 center);
		QL_SOURCE void set_outline_thickness(ql::f32 outline_thickness);
		QL_SOURCE void set_outline_color(ql::rgba outline_color);

		QL_SOURCE ql::vec2 get_center() const;
		QL_SOURCE void centerize();
		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		ql::vpoint point;
		ql::f32 radius;
		ql::f32 outline_thickness = 0.0f;
		ql::rgba outline_color = ql::rgba::unset();
	};

	struct circle_shape
	{
		circle_shape()
		{
		}

		circle_shape(const ql::vcircle& circle)
		{
			*this = circle;
		}

		circle_shape(const ql::circle_shape& circle)
		{
			*this = circle;
		}

		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QL_SOURCE ql::circle_shape& operator=(const ql::vcircle& circle);
		QL_SOURCE ql::circle_shape& operator=(const ql::circle_shape& circle);

		QL_SOURCE bool contains(ql::vec2 position) const;
		QL_SOURCE void centerize_origin();
		QL_SOURCE void set_radius(ql::f32 radius);
		QL_SOURCE ql::f32 get_radius() const;
		QL_SOURCE void set_position(ql::vec2 position);
		QL_SOURCE void set_center(ql::vec2 center);
		QL_SOURCE ql::vec2 get_center() const;
		QL_SOURCE ql::vec2 get_position() const;
		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE ql::rgba get_color() const;
		QL_SOURCE void set_outline_thickness(ql::f32 outline_thickness);
		QL_SOURCE ql::f32 get_outline_thickness() const;
		QL_SOURCE void set_outline_color(ql::rgba outline_color);
		QL_SOURCE ql::rgba get_outline_color() const;
		QL_SOURCE void set_point_count(ql::size count);
		QL_SOURCE ql::size get_point_count() const;

		sf::CircleShape shape;
	};

	struct vcircles
	{
		QL_SOURCE void resize(ql::size new_size);
		QL_SOURCE void reserve(ql::size new_size);

		QL_SOURCE ql::vcircle& operator[](ql::size index);
		QL_SOURCE const ql::vcircle& operator[](ql::size index) const;

		QL_SOURCE ql::vcircle& front();
		QL_SOURCE const ql::vcircle& front() const;

		QL_SOURCE ql::vcircle& back();
		QL_SOURCE const ql::vcircle& back() const;

		QL_SOURCE void add_circle(ql::vcircle circle);
		QL_SOURCE void add_circle(ql::vpoint point, ql::f32 radius, ql::rgba color);
		QL_SOURCE void add_circle(ql::vec2 position, ql::f32 radius, ql::rgba color);

		QL_SOURCE ql::size size() const;
		QL_SOURCE void clear();

		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		std::vector<ql::vcircle> circles;
	};

	struct circles
	{
		circles()
		{
		}

		circles(const ql::vcircles& circles)
		{
			*this = circles;
		}

		circles(const ql::circles& circles)
		{
			*this = circles;
		}

		QL_SOURCE void resize(ql::size new_size);
		QL_SOURCE void reserve(ql::size new_size);

		QL_SOURCE ql::circle_shape& operator[](ql::size index);
		QL_SOURCE const ql::circle_shape& operator[](ql::size index) const;

		QL_SOURCE ql::circle_shape& front();
		QL_SOURCE const ql::circle_shape& front() const;

		QL_SOURCE ql::circle_shape& back();
		QL_SOURCE const ql::circle_shape& back() const;

		QL_SOURCE void add_circle(const ql::vcircle& circle);
		QL_SOURCE void add_circle(const ql::circle_shape& circle);
		QL_SOURCE void add_circle(ql::vpoint point, ql::f32 radius, ql::rgba color);
		QL_SOURCE void add_circle(ql::vec2 position, ql::f32 radius, ql::rgba color);
		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QL_SOURCE ql::circles& operator=(const ql::vcircles& circles);
		QL_SOURCE ql::circles& operator=(const ql::circles& circles);

		QL_SOURCE ql::size size() const;
		QL_SOURCE void clear();

		std::vector<ql::circle_shape> circles_;
	};

	struct vline
	{
		QL_SOURCE void set_a(ql::vpoint point);
		QL_SOURCE void set_a(ql::vec2 position);
		QL_SOURCE void set_b(ql::vpoint point);
		QL_SOURCE void set_b(ql::vec2 position);
		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void set_a_color(ql::rgba color);
		QL_SOURCE void set_b_color(ql::rgba color);

		QL_SOURCE ql::vec2 normal() const;
		QL_SOURCE ql::f32 length() const;
		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		QL_SOURCE ql::vline& rotate_around_a(ql::f64 degree);
		QL_SOURCE ql::vline& rotate_around_b(ql::f64 degree);

		QL_SOURCE operator ql::straight_line() const;

		vpoint a;
		vpoint b;
	};

	struct line
	{
		line()
		{
		}

		line(ql::straight_line line)
		{
			*this = line;
		}

		QL_SOURCE void set_a(ql::vpoint point);
		QL_SOURCE void set_a(ql::vec2 position);
		QL_SOURCE void set_b(ql::vpoint point);
		QL_SOURCE void set_b(ql::vec2 position);
		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void set_a_color(ql::rgba color);
		QL_SOURCE void set_b_color(ql::rgba color);
		QL_SOURCE vpoint get_a() const;
		QL_SOURCE vpoint get_b() const;

		QL_SOURCE ql::vec2 normal() const;
		QL_SOURCE ql::f32 length() const;

		QL_SOURCE operator ql::straight_line() const;

		QL_SOURCE ql::line& operator=(const ql::vline& line);
		QL_SOURCE ql::line& operator=(const ql::straight_line& line);
		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		std::array<sf::Vertex, 2> vertices;
	};

	struct vlines
	{
		QL_SOURCE void resize(ql::size new_size);
		QL_SOURCE void reserve(ql::size new_size);

		QL_SOURCE ql::vpoint& operator[](ql::size index);
		QL_SOURCE const ql::vpoint& operator[](ql::size index) const;

		QL_SOURCE ql::vpoint& front();
		QL_SOURCE const ql::vpoint& front() const;

		QL_SOURCE ql::vpoint& back();
		QL_SOURCE const ql::vpoint& back() const;

		QL_SOURCE void clear();
		QL_SOURCE ql::size size() const;
		QL_SOURCE void add_point(ql::vpoint point);
		QL_SOURCE void add_point(ql::vec2 position, ql::rgba color = ql::rgba::white());
		QL_SOURCE void complete();

		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		std::vector<ql::vpoint> points;
	};

	struct lines
	{
		lines()
		{
			this->vertices.set_primitive_type(ql::primitive_type::line_strip);
		}

		lines(const ql::vlines& lines)
		{
			this->vertices.set_primitive_type(ql::primitive_type::line_strip);
			*this = lines;
		}

		QL_SOURCE void resize(ql::size new_size);
		QL_SOURCE void reserve(ql::size new_size);

		QL_SOURCE ql::vertex& operator[](ql::size index);
		QL_SOURCE const ql::vertex& operator[](ql::size index) const;

		QL_SOURCE ql::vertex& front();
		QL_SOURCE const ql::vertex& front() const;

		QL_SOURCE ql::vertex& back();
		QL_SOURCE const ql::vertex& back() const;

		QL_SOURCE void complete();

		QL_SOURCE ql::lines& operator=(const ql::vlines& lines);
		QL_SOURCE void clear();
		QL_SOURCE ql::size size() const;
		QL_SOURCE void add_point(ql::vpoint point);
		QL_SOURCE void add_point(ql::vec2 position, ql::rgba color = ql::rgba::white());
		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		ql::vertex_array vertices;
	};

	struct vthick_line
	{
		QL_SOURCE void set_a(ql::vpoint point);
		QL_SOURCE void set_a(ql::vec2 position);
		QL_SOURCE void set_b(ql::vpoint point);
		QL_SOURCE void set_b(ql::vec2 position);
		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void set_a_color(ql::rgba color);
		QL_SOURCE void set_b_color(ql::rgba color);

		QL_SOURCE ql::vpoints as_points() const;

		QL_SOURCE ql::vec2 normal() const;
		QL_SOURCE ql::f32 length() const;
		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		ql::vpoint a;
		ql::vpoint b;
		ql::f32 thickness = 1.0f;
	};

	struct thick_line
	{
		thick_line()
		{
		}

		thick_line(const ql::vthick_line& line)
		{
			*this = line;
		}

		QL_SOURCE void set_a(ql::vpoint point);
		QL_SOURCE void set_a(ql::vec2 position);
		QL_SOURCE void extend_a(ql::f32 delta);
		QL_SOURCE void set_b(ql::vpoint point);
		QL_SOURCE void set_b(ql::vec2 position);
		QL_SOURCE void extend_b(ql::f32 delta);
		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void set_a_color(ql::rgba color);
		QL_SOURCE void set_b_color(ql::rgba color);
		QL_SOURCE void set_thickness(ql::f32 thickness);
		QL_SOURCE void move(ql::vec2 delta);

		QL_SOURCE ql::vpoints as_points() const;
		QL_SOURCE ql::vec2 normal() const;
		QL_SOURCE ql::f32 length() const;
		QL_SOURCE ql::thick_line& operator=(const ql::vthick_line& line);
		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		std::array<sf::Vertex, 4> vertices;
	};

	struct vthick_lines
	{
		QL_SOURCE void resize(ql::size new_size);
		QL_SOURCE void reserve(ql::size new_size);

		QL_SOURCE ql::vpoint& operator[](ql::size index);
		QL_SOURCE const ql::vpoint& operator[](ql::size index) const;

		QL_SOURCE ql::vpoint& front();
		QL_SOURCE const ql::vpoint& front() const;

		QL_SOURCE ql::vpoint& back();
		QL_SOURCE const ql::vpoint& back() const;

		QL_SOURCE void add_thick_line(ql::vpoint point);
		QL_SOURCE void add_thick_line(ql::vec2 position, ql::rgba color);
		QL_SOURCE void set_thickness(ql::f32 thickness);
		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QL_SOURCE void clear();
		QL_SOURCE ql::size size() const;

		ql::vec2 position;
		ql::vpoints points;
		ql::f32 thickness = 1.0f;
	};

	struct thick_lines
	{
		thick_lines()
		{
			this->vertices.set_primitive_type(ql::primitive_type::quads);
		}

		QL_SOURCE void resize(ql::size new_size);
		QL_SOURCE void reserve(ql::size new_size);

		QL_SOURCE ql::vertex& operator[](ql::size index);
		QL_SOURCE const ql::vertex& operator[](ql::size index) const;

		QL_SOURCE ql::vertex& front();
		QL_SOURCE const ql::vertex& front() const;

		QL_SOURCE ql::vertex& back();
		QL_SOURCE const ql::vertex& back() const;

		QL_SOURCE void add_thick_line(ql::vpoint point, ql::f32 thickness);
		QL_SOURCE void add_thick_line(ql::vec2 position, ql::rgba color, ql::f32 thickness);

		QL_SOURCE void complete();

		QL_SOURCE ql::thick_lines& operator=(const ql::vthick_lines& lines);
		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QL_SOURCE void clear();
		QL_SOURCE ql::size size() const;
		QL_SOURCE bool empty() const;

		ql::vertex_array vertices;
	};

	struct transition_overlay
	{
		transition_overlay();

		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void set_slope(ql::f64 slope);

		QL_SOURCE void set_dimension(ql::vec2 dimension);
		QL_SOURCE void set_duration(ql::f64 duration);
		QL_SOURCE void make_disappear();
		QL_SOURCE void make_appear();
		QL_SOURCE void update(const ql::event& event);
		QL_SOURCE bool just_finished_disappearing() const;
		QL_SOURCE bool just_finished_appearing() const;
		QL_SOURCE void draw(ql::render& draw) const;

		ql::multiplied_color_extension<ql::rectangle> overlay;
		ql::animation animation;
		ql::f64 slope = 1.0;
	};

	struct pixel_image
	{
		pixel_image()
		{
			this->vertices.set_primitive_type(ql::primitive_type::quads);
		}

		QL_SOURCE void set_array_dimension(ql::vector2u dimension);
		QL_SOURCE void set_pixel_dimension(ql::vec2 dimension);
		QL_SOURCE void set_position(ql::vec2 position);
		QL_SOURCE void create_positions();

		QL_SOURCE void set(ql::size x, ql::size y, ql::rgba color);
		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		ql::vector2u array_dimension;
		ql::vec2 pixel_dimension;
		ql::vec2 position;
		ql::vertex_array vertices;
		bool positions_set = false;
	};

	struct text_stream_color
	{
		constexpr text_stream_color(ql::rgba color) : value(color)
		{
		}

		ql::rgba value;
	};

	struct text_stream_outline_color
	{
		constexpr text_stream_outline_color(ql::rgba color) : value(color)
		{
		}

		ql::rgba value;
	};

	struct text_stream_outline_thickness
	{
		constexpr text_stream_outline_thickness(ql::f32 thickness) : value(thickness)
		{
		}

		ql::f32 value;
	};

	struct text_stream_character_size
	{
		constexpr text_stream_character_size(ql::u32 size) : value(size)
		{
		}

		ql::u32 value;
	};

	struct text_stream_font
	{
		constexpr text_stream_font(std::string font) : value(font)
		{
		}

		std::string value;
	};

	struct text_stream_style
	{
		constexpr text_stream_style(sf::Text::Style style) : value(style)
		{
		}

		sf::Text::Style value;
	};

	struct text_stream_letter_spacing
	{
		constexpr text_stream_letter_spacing(ql::f32 spacing) : value(spacing)
		{
		}

		ql::f32 value;
	};

	struct text_stream_line_spacing
	{
		constexpr text_stream_line_spacing(ql::f32 spacing) : value(spacing)
		{
		}

		ql::f32 value;
	};

	struct text_stream_scale
	{
		constexpr text_stream_scale(ql::vec2 scale) : value(scale)
		{
		}

		ql::vec2 value;
	};

	struct text_stream_shift
	{
		constexpr text_stream_shift(ql::vec2 shift) : value(shift)
		{
		}

		ql::vec2 value;
	};

	struct text_stream_push
	{
		constexpr text_stream_push()
		{
		}
	};

	struct text_stream_pop
	{
		constexpr text_stream_pop()
		{
		}
	};

	struct text_stream_pop_push
	{
		constexpr text_stream_pop_push()
		{
		}
	};

	struct text_stream_new_line
	{
		constexpr text_stream_new_line(ql::f32 value) : value(value)
		{
		}

		ql::f32 value;
	};

	namespace ts
	{
		constexpr auto color(ql::rgba color)
		{
			return text_stream_color(color);
		}

		constexpr auto outline_color(ql::rgba color)
		{
			return text_stream_outline_color(color);
		}

		constexpr auto outline_thickness(ql::f32 thickness)
		{
			return text_stream_outline_thickness(thickness);
		}

		constexpr auto character_size(ql::u32 size)
		{
			return text_stream_character_size(size);
		}

		constexpr auto font(std::string font)
		{
			return text_stream_font(font);
		}

		constexpr auto style(sf::Text::Style style)
		{
			return text_stream_style(style);
		}

		constexpr auto letter_spacing(ql::f32 spacing)
		{
			return text_stream_letter_spacing(spacing);
		}

		constexpr auto line_spacing(ql::f32 spacing)
		{
			return text_stream_line_spacing(spacing);
		}

		constexpr auto scale(ql::f32 scale)
		{
			return text_stream_scale(ql::vec(scale, scale));
		}

		constexpr auto scale(ql::vec2 scale)
		{
			return text_stream_scale(scale);
		}

		constexpr auto shift(ql::vec2 shift)
		{
			return text_stream_shift(shift);
		}

		constexpr auto shift(ql::f32 x, ql::f32 y)
		{
			return text_stream_shift(ql::vec(x, y));
		}

		constexpr auto yshift(ql::f32 y)
		{
			return text_stream_shift(ql::vec(0.f, y));
		}

		constexpr auto xshift(ql::f32 x)
		{
			return text_stream_shift(ql::vec(x, 0.f));
		}

		constexpr auto push()
		{
			return text_stream_push();
		}

		constexpr auto pop()
		{
			return text_stream_pop();
		}

		constexpr auto pop_push()
		{
			return text_stream_pop_push();
		}

		constexpr auto endl(ql::f32 value = ql::f32_max)
		{
			return text_stream_new_line(value);
		}
	}	 // namespace ts

	template <typename T>
	constexpr bool is_text_stream_effect()
	{
		return ql::is_any_type_equal_to<
				T, text_stream_color, text_stream_outline_color, text_stream_outline_thickness, text_stream_character_size,
				text_stream_font, text_stream_style, text_stream_letter_spacing, text_stream_scale, text_stream_shift, text_stream_push,
				text_stream_pop, text_stream_pop_push, text_stream_new_line>();
	}

	struct text_stream
	{
		struct effect_state
		{
			std::string font;
			ql::rgba color;
			ql::rgba outline_color;
			ql::u32 character_size = 20u;
			ql::f32 outline_thickness = 0.0f;
			ql::f32 letter_spacing = 1.0f;
			ql::f32 line_spacing = 1.0f;
			ql::vec2 shift = ql::vec(0.0f, 0.0f);
			sf::Text::Style style = sf::Text::Style::Regular;
			ql::vec2 scale = ql::vec(1.0f, 1.0f);
		};

		struct element
		{
			ql::size text_index = ql::size_max;
			ql::size sprite_index = ql::size_max;
			ql::size line_index = 0u;
			ql::hitbox hitbox;
			ql::hitbox standard_hitbox;
			text_stream& ref;

			element(text_stream& stream) : ref(stream)
			{
			}

			void check_text() const
			{
				if (!this->is_text())
				{
					throw ql::exception("ql::text_stream::element: tried to access text, but text_index is not set");
				}
			}

			void check_sprite() const
			{
				if (!this->is_sprite())
				{
					throw ql::exception("ql::text_stream::element: tried to access sprite, but sprite_index is not set");
				}
			}

			element& operator=(const element& other)
			{
				this->text_index = other.text_index;
				this->sprite_index = other.sprite_index;
				this->hitbox = other.hitbox;
				this->standard_hitbox = other.standard_hitbox;
				return *this;
			}

			bool is_text() const
			{
				return this->text_index != ql::size_max;
			}

			bool is_sprite() const
			{
				return this->sprite_index != ql::size_max;
			}

			ql::text& get_text()
			{
				this->check_text();
				return this->ref.texts[this->text_index];
			}

			const ql::text& get_text() const
			{
				this->check_text();
				return this->ref.texts[this->text_index];
			}

			ql::sprite& get_sprite()
			{
				this->check_sprite();
				return this->ref.sprites[this->sprite_index];
			}

			const ql::sprite& get_sprite() const
			{
				this->check_sprite();
				return this->ref.sprites[this->sprite_index];
			}

			void set_string(const std::string& string)
			{
				this->ref.texts[this->text_index].set_string(string);
			}

			template <typename... Ts>
			requires (!(ql::variadic_size<Ts...>() == 1u && ql::is_same<std::string, ql::variadic_type<0u, Ts...>>()))
			void set_string(Ts&&... stuff)
			{
				this->set_string(ql::to_string(stuff...));
			}

			std::string get_string() const
			{
				return this->get_text().get_string();
			}

			std::wstring get_wstring() const
			{
				return this->get_text().get_wstring();
			}

			void calculate_hitbox()
			{
				if (this->is_text())
				{
					this->hitbox = this->get_text().get_visible_hitbox();
					this->standard_hitbox = this->get_text().get_standard_hitbox();
				}
				else if (this->is_sprite())
				{
					this->standard_hitbox = this->hitbox = this->get_sprite().get_hitbox();
				}
			}

			ql::vec2 get_right_side() const
			{
				return this->standard_hitbox.position + ql::vec(this->standard_hitbox.dimension.x, 0);
			}

			ql::vec2 get_position() const
			{
				return this->standard_hitbox.position;
			}

			void draw(ql::render& draw) const
			{
				if (this->is_text())
				{
					draw.draw(this->get_text());
				}
				else if (this->is_sprite())
				{
					draw.draw(this->get_sprite());
				}
			}
		};

		std::vector<effect_state> states;
		std::vector<element> elements;

		std::vector<ql::text> texts;
		std::vector<ql::sprite> sprites;
		ql::vec2 position;
		ql::vec2 next_position;
		bool currently_new_line = true;
		ql::size current_line = 0u;

		text_stream()
		{
			this->states.push_back({});
		}

		void new_line(ql::f32 y = ql::f32_max)
		{
			if (y == ql::f32_max)
			{
				auto line = this->elements.back().line_index;
				for (ql::size i = 0u; i < this->elements.size(); ++i)
				{
					if (this->elements[i].line_index == line && this->elements[i].is_text())
					{
						y = this->elements[i].get_text().get_line_spacing_pixels();
						break;
					}
				}
			}

			this->currently_new_line = true;
			this->next_position.x = this->position.x;
			this->next_position.y += y;
			++this->current_line;
		}

		void add_string(const std::string& string, bool check_new_line = true)
		{
			if (check_new_line)
			{
				ql::size last = 0u;
				for (ql::size i = 0u; i < string.length(); ++i)
				{
					if (string[i] == '\n')
					{
						if (i)
						{
							this->add_string(string.substr(last, i), false);
						}
						this->new_line();
						last = i + 1;
					}
				}
				this->add_string(string.substr(last, string.size()), false);
				return;
			}

			ql::f32 spacing = 0.0f;
			if (!this->elements.empty() && !currently_new_line)
			{
				const auto& element = this->elements.back();
				if (element.is_text())
				{
					spacing = element.get_text().get_next_character_advance();
				}
				else if (element.is_sprite())
				{
					spacing = element.hitbox.dimension.x;
				}
				this->next_position.x += spacing;
			}
			// ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", "for ", string, " - spacing = ", spacing, " position.x = ", this->next_position.x);

			this->elements.push_back({*this});
			auto& element = this->elements.back();
			element.text_index = this->texts.size();
			this->texts.push_back({});

			this->apply_state();

			element.get_text().set_string(string);

			this->currently_new_line = false;

			element.get_text().set_position(this->next_position + this->states.back().shift);
			element.calculate_hitbox();
			element.line_index = this->current_line;
		}

		void add_texture(const sf::Texture& texture)
		{
			ql::f32 spacing = 0.0f;
			if (!this->elements.empty() && !currently_new_line)
			{
				const auto& element = this->elements.back();
				if (element.is_text())
				{
					spacing = element.get_text().get_next_character_advance();
				}
				else if (element.is_sprite())
				{
					spacing = element.hitbox.dimension.x;
				}
				this->next_position.x += spacing;
			}

			this->elements.push_back({*this});
			auto& element = this->elements.back();
			element.sprite_index = this->sprites.size();
			this->sprites.push_back({});

			this->apply_state();

			element.get_sprite().set_texture(texture);

			this->currently_new_line = false;

			element.get_sprite().set_position(this->next_position + this->states.back().shift);
			element.calculate_hitbox();
			element.line_index = this->current_line;
		}

		template <typename T>
		void add_effect(const T& effect)
		{
			if constexpr (ql::is_same<T, text_stream_color>())
			{
				this->states.back().color = effect.value;
			}
			else if constexpr (ql::is_same<T, text_stream_outline_color>())
			{
				this->states.back().outline_color = effect.value;
			}
			else if constexpr (ql::is_same<T, text_stream_outline_thickness>())
			{
				this->states.back().outline_thickness = effect.value;
			}
			else if constexpr (ql::is_same<T, text_stream_character_size>())
			{
				this->states.back().character_size = effect.value;
			}
			else if constexpr (ql::is_same<T, text_stream_font>())
			{
				this->states.back().font = effect.value;
			}
			else if constexpr (ql::is_same<T, text_stream_style>())
			{
				this->states.back().style = effect.value;
			}
			else if constexpr (ql::is_same<T, text_stream_letter_spacing>())
			{
				this->states.back().letter_spacing = effect.value;
			}
			else if constexpr (ql::is_same<T, text_stream_scale>())
			{
				this->states.back().scale = effect.value;
			}
			else if constexpr (ql::is_same<T, text_stream_shift>())
			{
				this->states.back().shift += effect.value;
			}
			else if constexpr (ql::is_same<T, text_stream_push>())
			{
				this->add_state();
			}
			else if constexpr (ql::is_same<T, text_stream_pop>())
			{
				if (this->states.size() > 1u)
				{
					this->states.pop_back();
				}
			}
			else if constexpr (ql::is_same<T, text_stream_pop_push>())
			{
				if (this->states.size() > 1u)
				{
					this->states.pop_back();
				}
				this->add_state();
			}
			else if constexpr (ql::is_same<T, text_stream_new_line>())
			{
				this->new_line(effect.value);
			}
		}

		template <typename T>
		requires (!is_text_stream_effect<T>())
		text_stream& operator<<(const T& n)
		{
			if constexpr (ql::is_same<T, sf::Texture>())
			{
				this->add_texture(n);
			}
			else
			{
				this->add_string(ql::to_string(n));
			}
			return *this;
		}

		template <typename T>
		requires (is_text_stream_effect<T>())
		text_stream& operator<<(const T& n)
		{
			this->add_effect(n);
			return *this;
		}

		text_stream& operator=(const text_stream& other)
		{
			this->position = other.position;
			this->next_position = other.next_position;
			this->states = other.states;
			this->elements.clear();
			for (ql::size i = 0u; i < other.elements.size(); ++i)
			{
				this->elements.push_back({*this});
				this->elements.back() = other.elements[i];
			}
			return *this;
		}

		element& operator[](ql::size index)
		{
			return this->elements[index];
		}

		const element& operator[](ql::size index) const
		{
			return this->elements[index];
		}

		element& front()
		{
			return this->elements.front();
		}

		const element& front() const
		{
			return this->elements.front();
		}

		element& back()
		{
			return this->elements.back();
		}

		const element& back() const
		{
			return this->elements.back();
		}

		ql::size size() const
		{
			return this->elements.size();
		}

		ql::f32 line_height(ql::size index) const
		{
			ql::f32 result = ql::f32_min;

			bool first = true;
			for (auto& element : this->elements)
			{
				if (element.line_index == index)
				{
					result = ql::max(result, element.hitbox.position.y);
				}
			}
			return result;
		}

		ql::hitbox line_hitbox(ql::size index) const
		{
			ql::hitbox result;
			result.position = ql::vec(ql::f32_max, ql::f32_max);
			result.dimension = ql::vec(0.0f, 0.0f);

			ql::vec2 last_position;

			bool first = true;
			for (auto& element : this->elements)
			{
				if (element.line_index == index)
				{
					if (first)
					{
						result.position.x = element.hitbox.position.x;
						first = false;
					}
					last_position = element.hitbox.position;
					result.position.y = ql::min(result.position.y, element.hitbox.position.y);
					result.dimension.x = element.hitbox.dimension.x;
					result.dimension.y = ql::max(result.dimension.y, element.hitbox.dimension.y);
				}
			}
			result.dimension.x += (last_position.x - result.position.x);
			return result;
		}

		ql::size lines() const
		{
			if (this->elements.empty())
				return 0u;
			return this->elements.back().line_index + 1u;
		}

		ql::hitbox hitbox() const
		{
			if (!this->lines())
			{
				return {};
			}
			ql::hitbox result;
			auto first = this->line_hitbox(0u);

			ql::f32 x = first.dimension.x;
			for (ql::size i = 1u; i < this->lines(); ++i)
			{
				x = ql::max(x, this->line_hitbox(i).dimension.x);
			}

			auto last = this->line_hitbox(this->lines() - 1);

			auto y = (last.position.y - first.position.y) + last.dimension.y;

			result.position = first.position;
			result.dimension = ql::vec(x, y);
			return result;
		}

		ql::hitbox get_visible_hitbox() const
		{
			return this->hitbox();
		}

		void set_string(const std::string& string)
		{
			this->clear();
			this->operator<<(string);
		}

		void clear()
		{
			this->states.resize(1u);
			this->states.front().shift = ql::vec(0, 0);
			this->elements.clear();
			this->sprites.clear();
			this->texts.clear();
			this->next_position = this->position;
			this->currently_new_line = true;
			this->current_line = 0u;
		}

		void set_position(ql::vec2 position)
		{
			auto delta = position - this->position;
			this->position = position;
			this->next_position = position;

			for (auto& i : this->elements)
			{
				i.hitbox.move(delta);
				i.standard_hitbox.move(delta);
				if (i.is_sprite())
				{
					i.get_sprite().move(delta);
				}
				else if (i.is_text())
				{
					i.get_text().move(delta);
				}
			}
		}

		void move(ql::vec2 delta)
		{
			this->set_position(this->position + delta);
		}

		void set_font(std::string name)
		{
			this->states.front().font = name;
		}

		void set_character_size(ql::u32 character_size)
		{
			this->states.front().character_size = character_size;
		}

		void set_color(ql::rgba color)
		{
			this->states.front().color = color;
		}

		void set_outline_color(ql::rgba color)
		{
			this->states.front().outline_color = color;
		}

		void set_outline_thickness(ql::f32 thickness)
		{
			this->states.front().outline_thickness = thickness;
		}

		void set_style(sf::Text::Style style)
		{
			this->states.front().style = style;
		}

		void set_letter_spacing(ql::f32 letter_spacing)
		{
			this->states.front().letter_spacing = letter_spacing;
		}

		void set_line_spacing(ql::f32 line_spacing)
		{
			this->states.front().line_spacing = line_spacing;
		}

		void draw(ql::render& draw) const
		{
			draw.draw(this->elements);
		}

		void add_state()
		{
			this->states.push_back(this->states.back());
		}

		void apply_state()
		{
			auto& element = this->elements.back();
			auto& state = this->states.back();

			if (element.is_text())
			{
				element.get_text().set_font(state.font);
				element.get_text().set_character_size(state.character_size);
				element.get_text().set_color(state.color);
				element.get_text().set_outline_thickness(state.outline_thickness);
				element.get_text().set_outline_color(state.outline_color);
				element.get_text().set_style(state.style);
				element.get_text().set_letter_spacing(state.letter_spacing);
				element.get_text().set_line_spacing(state.line_spacing);
			}
			else if (element.is_sprite())
			{
				element.get_sprite().set_color(state.color);
				element.get_sprite().set_scale(state.scale);
			}
		}
	};

	struct tile_map
	{
		QL_SOURCE void set_texture_ptr(const sf::Texture& texture, ql::vector2u texture_tile_dimension);
		QL_SOURCE void set_texture_ptr(const sf::Texture& texture, ql::u32 texture_tile_width);
		QL_SOURCE void set_position(ql::vec2 position);

		// pair.first = index - pair.second = rotation (0-7)
		QL_SOURCE void
		create(const std::vector<std::pair<ql::u32, ql::u32>>& indices_and_rotations, ql::size index_width, ql::rgba color);
		// pair.first = index - pair.second = rotation (0-7)
		QL_SOURCE void create(const std::vector<std::pair<ql::u32, ql::u32>>& indices_and_rotations, ql::size index_width);

		// pair.first = index - pair.second = rotation (0-360)
		QL_SOURCE void
		create(const std::vector<std::pair<ql::u32, ql::f32>>& indices_and_rotations, ql::size index_width, ql::rgba color);
		// pair.first = index - pair.second = rotation (0-360)
		QL_SOURCE void create(const std::vector<std::pair<ql::u32, ql::f32>>& indices_and_rotations, ql::size index_width);

		QL_SOURCE void create(const std::vector<ql::u32>& indices, ql::size index_width, ql::rgba color);
		QL_SOURCE void create(const std::vector<ql::u32>& indices, ql::size index_width);

		// pair.first = index - pair.second = rotation (0-7)
		QL_SOURCE void create_skip_empty(
				const std::vector<std::pair<ql::u32, ql::u32>>& indices_and_rotations,
				ql::size index_width,
				ql::rgba color,
				ql::u32 skip_index = 0u
		);
		// pair.first = index - pair.second = rotation (0-7)
		QL_SOURCE void create_skip_empty(
				const std::vector<std::pair<ql::u32, ql::u32>>& indices_and_rotations,
				ql::size index_width,
				ql::u32 skip_index = 0u
		);

		// pair.first = index - pair.second = rotation (0-360)
		QL_SOURCE void create_skip_empty(
				const std::vector<std::pair<ql::u32, ql::f32>>& indices_and_rotations,
				ql::size index_width,
				ql::rgba color,
				ql::u32 skip_index = 0u
		);
		// pair.first = index - pair.second = rotation (0-360)
		QL_SOURCE void create_skip_empty(
				const std::vector<std::pair<ql::u32, ql::f32>>& indices_and_rotations,
				ql::size index_width,
				ql::u32 skip_index = 0u
		);

		QL_SOURCE void
		create_skip_empty(const std::vector<ql::u32>& indices, ql::size index_width, ql::rgba color, ql::u32 skip_index = 0u);
		QL_SOURCE void create_skip_empty(const std::vector<ql::u32>& indices, ql::size index_width, ql::u32 skip_index = 0u);

		template <typename C>
		requires (ql::is_container<C>() && ql::has_size<C>())
		void create_skip_empty(const C& indices, ql::size index_width, ql::u32 skip_index = 0u, ql::rgba color = ql::rgba::white())
		{
			if (!this->texture_ptr_set)
			{
				ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", "tile_map::create: texture_ptr not set");
				return;
			}

			this->chunks.clear();
			this->color = color;

			auto chunk_width = (index_width - 1) / this->max_chunk_size.x + 1;
			auto chunk_height = (indices.size() / index_width - 1) / this->max_chunk_size.y + 1;
			auto chunk_dim = chunk_width * chunk_height;

			this->chunk_width_count = chunk_width;
			this->chunks.resize(chunk_dim);
			for (auto& chunk : this->chunks)
			{
				chunk.setPrimitiveType(sf::Quads);
			}

			auto texture_row_tile_count = texture_ptr->getSize().x / this->texture_tile_dimension.x;

			ql::u32 ctr = 0;
			if (color == ql::rgba::white())
			{
				for (ql::u32 i = 0; i < indices.size(); ++i)
				{
					auto index = indices[i];
					if (index == skip_index)
					{
						continue;
					}
					auto chunk_x = (i % index_width) / this->max_chunk_size.x;
					auto chunk_y = (i / index_width) / this->max_chunk_size.y;
					auto chunk_index = chunk_x + chunk_y * chunk_width;

					auto& chunk = this->chunks[chunk_index];
					auto ctr = chunk.getVertexCount();
					chunk.resize(ctr + 4);

					auto [y, x] = ql::div_mod(i, index_width);

					auto tile_x = (index % texture_row_tile_count);
					auto tile_y = (index / texture_row_tile_count);

					chunk[ctr + 0].position =
							this->position + ql::vector2u(x * this->position_tile_dimension.x, y * this->position_tile_dimension.y);
					chunk[ctr + 1].position =
							this->position + ql::vector2u((x + 1) * this->position_tile_dimension.x, y * this->position_tile_dimension.y);
					chunk[ctr + 2].position =
							this->position + ql::vector2u((x + 1) * this->position_tile_dimension.x, (y + 1) * this->position_tile_dimension.y);
					chunk[ctr + 3].position =
							this->position + ql::vector2u(x * this->position_tile_dimension.x, (y + 1) * this->position_tile_dimension.y);

					chunk[ctr + 0].texCoords =
							ql::vector2u(tile_x * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
					chunk[ctr + 1].texCoords =
							ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
					chunk[ctr + 2].texCoords =
							ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);
					chunk[ctr + 3].texCoords =
							ql::vector2u(tile_x * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);
				}
			}
			else
			{
				for (ql::u32 i = 0; i < indices.size(); ++i)
				{
					auto index = indices[i];
					if (index == skip_index)
					{
						continue;
					}

					auto chunk_x = (i % index_width) / this->max_chunk_size.x;
					auto chunk_y = (i / index_width) / this->max_chunk_size.y;
					auto chunk_index = chunk_x + chunk_y * chunk_width;

					auto& chunk = this->chunks[chunk_index];
					auto ctr = chunk.getVertexCount();
					chunk.resize(ctr + 4);

					auto [y, x] = ql::div_mod(i, index_width);
					auto tile_x = (index % texture_row_tile_count);
					auto tile_y = (index / texture_row_tile_count);

					chunk[ctr + 0].position =
							this->position + ql::vector2u(x * this->position_tile_dimension.x, y * this->position_tile_dimension.y);
					chunk[ctr + 1].position =
							this->position + ql::vector2u((x + 1) * this->position_tile_dimension.x, y * this->position_tile_dimension.y);
					chunk[ctr + 2].position =
							this->position + ql::vector2u((x + 1) * this->position_tile_dimension.x, (y + 1) * this->position_tile_dimension.y);
					chunk[ctr + 3].position =
							this->position + ql::vector2u(x * this->position_tile_dimension.x, (y + 1) * this->position_tile_dimension.y);

					chunk[ctr + 0].color = color;
					chunk[ctr + 1].color = color;
					chunk[ctr + 2].color = color;
					chunk[ctr + 3].color = color;

					chunk[ctr + 0].texCoords =
							ql::vector2u(tile_x * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
					chunk[ctr + 1].texCoords =
							ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, tile_y * this->texture_tile_dimension.y);
					chunk[ctr + 2].texCoords =
							ql::vector2u((tile_x + 1) * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);
					chunk[ctr + 3].texCoords =
							ql::vector2u(tile_x * this->texture_tile_dimension.x, (tile_y + 1) * this->texture_tile_dimension.y);
				}
			}
		}

		QL_SOURCE void set_color(ql::rgba color);

		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QL_SOURCE ql::size size() const;
		QL_SOURCE ql::size chunk_count() const;
		QL_SOURCE void set_chunk_dimension(ql::u32 x, ql::u32 y);
		QL_SOURCE void clear();

		ql::vector2u max_chunk_size = {ql::u32_max, ql::u32_max};
		ql::size chunk_width_count = 0u;
		std::vector<sf::VertexArray> chunks;
		const sf::Texture* texture_ptr;
		bool texture_ptr_set = false;
		ql::vector2u texture_tile_dimension;
		ql::vector2u position_tile_dimension;
		ql::vec2 position;

		ql::rgba color;
	};

	namespace detail
	{
		template <typename T>
		concept has_light_c = requires(const T x) {
			{ x.light() } -> std::convertible_to<ql::f64>;
		};

		template <typename T>
		constexpr bool has_light()
		{
			return has_light_c<T>;
		}
	}	 // namespace detail

	struct small_tile_map
	{
		ql::vertex_array vertices;
		ql::vec2 position;
		const sf::Texture* texture_ptr;
		ql::vec2 scale = {1, 1};
		ql::vector2u texture_tile_dimension;

		QL_SOURCE void set_texture(const sf::Texture& texture, ql::u32 texture_tile_width);
		QL_SOURCE void set_position(ql::vec2 position);
		QL_SOURCE void set_scale(ql::vec2 scale);
		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		template <typename C>
		requires (ql::is_container<C>() && ql::has_size<C>())
		void create(const C& indices, ql::size index_width)
		{
			if (!this->texture_ptr)
			{
				ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", "small_tile_map::create: texture_ptr not set");
				return;
			}

			this->vertices.clear();
			this->vertices.set_primitive_type(sf::Quads);
			this->vertices.resize(indices.size() * 4);

			auto texture_row_tile_count = this->texture_ptr->getSize().x / this->texture_tile_dimension.x;

			ql::u32 ctr = 0;
			for (ql::u32 i = 0; i < indices.size(); ++i)
			{
				auto index = indices[i];

				auto [y, x] = ql::div_mod(i, index_width);

				auto tile_x = (index % texture_row_tile_count);
				auto tile_y = (index / texture_row_tile_count);

				this->vertices[ctr + 0].position = ql::vector2u(x, y) * this->scale * this->texture_tile_dimension;
				this->vertices[ctr + 1].position = ql::vector2u((x + 1), y) * this->scale * this->texture_tile_dimension;
				this->vertices[ctr + 2].position = ql::vector2u((x + 1), (y + 1)) * this->scale * this->texture_tile_dimension;
				this->vertices[ctr + 3].position = ql::vector2u(x, (y + 1)) * this->scale * this->texture_tile_dimension;

				this->vertices[ctr + 0].tex_coords = ql::vector2u(tile_x, tile_y) * this->texture_tile_dimension;
				this->vertices[ctr + 1].tex_coords = ql::vector2u((tile_x + 1), tile_y) * this->texture_tile_dimension;
				this->vertices[ctr + 2].tex_coords = ql::vector2u((tile_x + 1), (tile_y + 1)) * this->texture_tile_dimension;
				this->vertices[ctr + 3].tex_coords = ql::vector2u(tile_x, (tile_y + 1)) * this->texture_tile_dimension;
				ctr += 4;
			}
		}

		void create(ql::size index, ql::vec2 dimension)
		{
			if (!this->texture_ptr)
			{
				throw ql::exception("small_tile_map::create: texture_ptr not set");
			}

			ql::vector2u dim = (dimension - 1) / (this->scale * this->texture_tile_dimension) + 1;
			ql::vec2 dimf = (dimension) / (this->scale * this->texture_tile_dimension);

			this->vertices.clear();
			this->vertices.set_primitive_type(sf::Quads);
			this->vertices.resize(dim.x * dim.y * 4);

			auto texture_row_tile_count = this->texture_ptr->getSize().x / this->texture_tile_dimension.x;

			ql::u32 ctr = 0;
			for (ql::u32 i = 0; i < dim.x * dim.y; ++i)
			{
				auto [y, x] = ql::div_mod(i, dim.x);

				auto tile_x = (index % texture_row_tile_count);
				auto tile_y = (index / texture_row_tile_count);

				ql::f64 dx = 1.0;
				ql::f64 dy = 1.0;

				if (x == ql::u32_cast(dimf.x))
				{
					dx = std::fmod(dimf.x, 1.0);
				}
				if (y == ql::u32_cast(dimf.y))
				{
					dy = std::fmod(dimf.y, 1.0);
				}
				auto pos1 = ql::vec(x, y) * this->scale * this->texture_tile_dimension;
				auto pos2 = ql::vec(x + dx, y + dy) * this->scale * this->texture_tile_dimension;

				this->vertices[ctr + 0].position = ql::vec(pos1.x, pos1.y);
				this->vertices[ctr + 1].position = ql::vec(pos2.x, pos1.y);
				this->vertices[ctr + 2].position = ql::vec(pos2.x, pos2.y);
				this->vertices[ctr + 3].position = ql::vec(pos1.x, pos2.y);

				this->vertices[ctr + 0].tex_coords = ql::vec(tile_x, tile_y) * this->texture_tile_dimension;
				this->vertices[ctr + 1].tex_coords = ql::vec(tile_x + dx, tile_y) * this->texture_tile_dimension;
				this->vertices[ctr + 2].tex_coords = ql::vec(tile_x + dx, tile_y + dy) * this->texture_tile_dimension;
				this->vertices[ctr + 3].tex_coords = ql::vec(tile_x, tile_y + dy) * this->texture_tile_dimension;

				ctr += 4;
			}
		}

		void create_fill(ql::size index, ql::size x, ql::size y)
		{
			std::vector<ql::size> indices(x * y);
			ql::fill(indices, index);
			this->create(indices, x);
		}

		template <typename C>
		requires (ql::is_container<C>() && ql::has_size<C>() && ql::detail::has_light<ql::container_subtype<C>>())
		void create_light(
				const C& indices,
				ql::size index_width,
				ql::rgba no_light = ql::rgba::black(),
				ql::rgba full_light = ql::rgba::white()
		)
		{
			if (!this->texture_ptr)
			{
				ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", "small_tile_map::create: texture_ptr not set");
				return;
			}

			this->vertices.clear();
			this->vertices.set_primitive_type(sf::Quads);
			this->vertices.resize(indices.size() * 4);

			auto texture_row_tile_count = this->texture_ptr->getSize().x / this->texture_tile_dimension.x;

			ql::u32 ctr = 0;
			for (ql::u32 i = 0; i < indices.size(); ++i)
			{
				auto index = indices[i];
				// if (index == skip_index) {
				//	continue;
				// }

				auto [y, x] = ql::div_mod(i, index_width);

				auto tile_x = (index % texture_row_tile_count);
				auto tile_y = (index / texture_row_tile_count);

				this->vertices[ctr + 0].position = (ql::vector2u(x, y) * this->scale * this->texture_tile_dimension);
				this->vertices[ctr + 1].position = (ql::vector2u((x + 1), y) * this->scale * this->texture_tile_dimension);
				this->vertices[ctr + 2].position = (ql::vector2u((x + 1), (y + 1)) * this->scale * this->texture_tile_dimension);
				this->vertices[ctr + 3].position = (ql::vector2u(x, (y + 1)) * this->scale * this->texture_tile_dimension);

				this->vertices[ctr + 0].tex_coords = ql::vector2u(tile_x, tile_y) * this->texture_tile_dimension;
				this->vertices[ctr + 1].tex_coords = ql::vector2u((tile_x + 1), tile_y) * this->texture_tile_dimension;
				this->vertices[ctr + 2].tex_coords = ql::vector2u((tile_x + 1), (tile_y + 1)) * this->texture_tile_dimension;
				this->vertices[ctr + 3].tex_coords = ql::vector2u(tile_x, (tile_y + 1)) * this->texture_tile_dimension;

				this->vertices[ctr + 0].color = no_light.interpolated(full_light, indices[i].light());
				this->vertices[ctr + 1].color = no_light.interpolated(full_light, indices[i].light());
				this->vertices[ctr + 2].color = no_light.interpolated(full_light, indices[i].light());
				this->vertices[ctr + 3].color = no_light.interpolated(full_light, indices[i].light());
				ctr += 4;
			}
		}

		template <typename C>
		requires (ql::is_container<C>() && ql::has_size<C>())
		void create_skip_empty(const C& indices, ql::size index_width, ql::u32 skip_index)
		{
			if (!this->texture_ptr)
			{
				ql::println(ql::color::bright_yellow, "core ", ql::color::bright_gray, ":: ", "small_tile_map::create: texture_ptr not set");
				return;
			}

			this->vertices.clear();
			this->vertices.set_primitive_type(sf::Quads);
			this->vertices.resize(indices.size() * 4);

			auto texture_row_tile_count = this->texture_ptr->getSize().x / this->texture_tile_dimension.x;

			ql::u32 ctr = 0;
			for (ql::u32 i = 0; i < indices.size(); ++i)
			{
				auto index = indices[i];
				if (index == skip_index)
				{
					continue;
				}

				auto [y, x] = ql::div_mod(i, index_width);

				auto tile_x = (index % texture_row_tile_count);
				auto tile_y = (index / texture_row_tile_count);

				this->vertices[ctr + 0].position = ql::vector2u(x, y) * this->scale * this->texture_tile_dimension;
				this->vertices[ctr + 1].position = ql::vector2u((x + 1), y) * this->scale * this->texture_tile_dimension;
				this->vertices[ctr + 2].position = ql::vector2u((x + 1), (y + 1)) * this->scale * this->texture_tile_dimension;
				this->vertices[ctr + 3].position = ql::vector2u(x, (y + 1)) * this->scale * this->texture_tile_dimension;

				this->vertices[ctr + 0].tex_coords = ql::vector2u(tile_x, tile_y) * this->texture_tile_dimension;
				this->vertices[ctr + 1].tex_coords = ql::vector2u((tile_x + 1), tile_y) * this->texture_tile_dimension;
				this->vertices[ctr + 2].tex_coords = ql::vector2u((tile_x + 1), (tile_y + 1)) * this->texture_tile_dimension;
				this->vertices[ctr + 3].tex_coords = ql::vector2u(tile_x, (tile_y + 1)) * this->texture_tile_dimension;
				ctr += 4;
			}
		}
	};

	struct vgraph
	{
		vgraph()
		{
			this->x_axis_string_function = [](ql::size index) { return ql::to_string(index); };
			this->closest_graph_at_cursor_text.set_character_size(30);
			this->closest_graph_at_cursor_text.set_style(sf::Text::Style::Bold);
			this->closest_graph_at_cursor_background.set_outline_thickness(2);
		}

		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;

		struct highlighted_line
		{
			ql::rgba color;
			ql::f64 thickness = 0.0;
			bool foreground = true;
		};

		struct data_point_info
		{
			ql::f64 data = 0.0;
			ql::f64 thickness = ql::f64_min;
			ql::frgba color = ql::rgba::unset();

			ql::vcircle circle;
			ql::vtext text;

			data_point_info()
			{
				this->thickness = ql::f64_min;
				this->color = ql::frgba::unset();
			}

			data_point_info(ql::f64 value)
			{
				this->data = value;
			}

			data_point_info(const data_point_info& other)
			{
				this->data = other.data;
				this->color = other.color;
				this->thickness = other.thickness;
				this->circle = other.circle;
				this->text = other.text;
			}

			QL_SOURCE data_point_info& operator=(const data_point_info& other);

			QL_SOURCE data_point_info operator*(ql::f64 n) const;
			QL_SOURCE data_point_info operator*(data_point_info other) const;
			QL_SOURCE data_point_info operator-(data_point_info other) const;
			QL_SOURCE data_point_info operator+(data_point_info other) const;
			QL_SOURCE bool operator<(data_point_info other) const;
			QL_SOURCE bool operator>(data_point_info other) const;
		};

		struct data_point
		{
			ql::f64 data = 0.0;
			ql::f64 thickness = ql::f64_min;
			ql::frgba color = ql::rgba::unset();

			data_point()
			{
			}

			data_point(ql::f64 data) : data(data)
			{
			}

			data_point(const data_point& other)
			{
				this->data = other.data;
				this->color = other.color;
				this->thickness = other.thickness;
			}

			QL_SOURCE data_point& operator=(const data_point& other);

			QL_SOURCE data_point operator*(ql::f64 n) const;
			QL_SOURCE data_point operator*(data_point other) const;
			QL_SOURCE data_point operator-(data_point other) const;
			QL_SOURCE data_point operator+(data_point other) const;
			QL_SOURCE bool operator<(data_point other) const;
			QL_SOURCE bool operator>(data_point other) const;
		};

		struct data_point_simple
		{
			ql::f64 data = 0.0;

			data_point_simple()
			{
			}

			data_point_simple(ql::f64 data) : data(data)
			{
			}

			data_point_simple(const data_point_simple& other)
			{
				this->data = other.data;
			}

			QL_SOURCE data_point_simple& operator=(const data_point_simple& other);

			QL_SOURCE data_point_simple operator*(ql::f64 n) const;
			QL_SOURCE data_point_simple operator*(data_point_simple other) const;
			QL_SOURCE data_point_simple operator-(data_point_simple other) const;
			QL_SOURCE data_point_simple operator+(data_point_simple other) const;
			QL_SOURCE bool operator<(data_point_simple other) const;
			QL_SOURCE bool operator>(data_point_simple other) const;
		};

		ql::f64 min_min_value = ql::f64_min;
		ql::f64 min_max_value = ql::f64_max;
		ql::f64 max_min_value = ql::f64_min;
		ql::f64 max_max_value = ql::f64_max;

		ql::f64 height_delta = 0.1;

		ql::rgba x_axis_color = ql::rgba::unset();
		ql::rgba y_axis_color = ql::rgba::unset();
		ql::rgba axis_color = ql::rgba::white();
		ql::f64 y_axis_text_space = 40.0;
		ql::size desired_y_axis_lines = 10u;
		ql::vtext y_axis_text;
		bool y_axis_text_left = true;
		bool y_axis_text_percent = false;
		bool y_axis_text_integer = false;
		ql::size y_axis_text_precision = 3u;
		bool use_y_axis = true;
		bool y_axis_start_at_0 = false;
		ql::f64 y_axis_padding = 0.1;

		ql::f64 x_axis_text_space = 5.0;
		mutable ql::size x_axis_line_frequency = 200u;
		ql::vtext x_axis_text;
		bool x_axis_text_left = true;
		bool x_axis_text_percent = false;
		ql::size x_axis_text_precision = 3u;

		ql::size x_data_steps = 10u;
		ql::u32 desired_x_axis_lines = 10u;
		ql::u32 desired_visible_size = 200u;

		bool allow_dragging = true;
		bool enable_last_n_when_dragging_right_lock = false;
		ql::size display_last_n_entries = ql::size_max;
		ql::size index_start = 0u;
		ql::size index_end = ql::size_max;
		mutable ql::size index_skip_size = 1u;
		mutable std::pair<ql::size, ql::size> visible_index_range_before = {ql::size_max, ql::size_max};

		bool use_x_axis = true;
		std::function<std::string(ql::size)> x_axis_string_function;
		std::function<std::string(ql::f64)> y_axis_string_function;
		std::function<std::string(ql::f64)> y_axis_cursor_string_function;

		ql::rgba axis_line_color = ql::rgba(30, 30, 30);
		ql::f64 axis_thickness = 1.5f;

		std::string font;
		ql::f64 zoom_factor = 1.3;
		ql::vec2 position;
		ql::vec2 dimension = {500, 300};

		mutable ql::vec2 low_high_graph;
		std::string closest_graph_at_cursor = "";
		ql::f64 closest_graph_at_cursor_value = ql::f64_max;
		ql::u32 closest_graph_at_cursor_index = ql::u32_max;
		ql::rgba closest_graph_at_cursor_color;
		ql::f32 closest_graph_at_cursor_distance = 40.0f;
		ql::f32 closest_graph_at_cursor_multiply_thickness = 2.0f;
		ql::vec2 mouse_position;
		bool display_closest_graph_at_cursor = true;

		ql::vtext closest_graph_at_cursor_text;
		ql::vrectangle closest_graph_at_cursor_background;
		bool closest_graph_at_cursor_background_is_graph_background = true;
		std::function<std::string(std::string, ql::f64, ql::u32)> closest_graph_at_cursor_string_function;

		enum class interpolation_type : ql::u32
		{
			unset = 0,
			linear = 1,
			cubic = 2,
		};

		ql::rgba color = ql::rgba::white();
		ql::f64 thickness = 1.0f;
		interpolation_type interpolation = interpolation_type::cubic;
		ql::size interpolation_steps = 1u;

		struct info_graph
		{
			template <typename T>
			void set_data(const std::vector<T>& data)
			{
				this->data.resize(data.size());
				for (ql::u32 i = 0u; i < data.size(); ++i)
				{
					this->data[i].data = static_cast<ql::f64>(data[i]);
					this->data[i].color = this->color;
					this->data[i].thickness = this->thickness;
				}
			}

			template <typename T>
			void set_data(const std::vector<T>& data, ql::rgba color, ql::f64 thickness)
			{
				this->color = color;
				this->thickness = thickness;
				this->set_data(data);
			}

			QL_SOURCE void add_data(ql::f64 data);
			QL_SOURCE void add_data(ql::f64 data, ql::rgba color);
			QL_SOURCE void add_data(ql::f64 data, ql::rgba color, ql::f64 thickness);
			QL_SOURCE void add_data(ql::f64 data, std::string string);
			QL_SOURCE void add_data(ql::f64 data, std::string string, ql::rgba color);

			QL_SOURCE void set_font(const std::string& font);
			QL_SOURCE void set_text_color(ql::rgba text_color);
			QL_SOURCE void set_text_character_size(ql::u32 character_size);
			QL_SOURCE void set_text_style(ql::u32 text_style);
			QL_SOURCE void set_text_outline_thickness(ql::f32 thickness);
			QL_SOURCE void set_text_outline_color(ql::rgba color);

			QL_SOURCE ql::f64 get_percentage_height_at(ql::size index) const;
			QL_SOURCE std::pair<data_point_info, data_point_info> get_low_high() const;
			QL_SOURCE ql::size size() const;
			QL_SOURCE void clear();
			QL_SOURCE data_point_info& operator[](ql::size index);
			QL_SOURCE const data_point_info& operator[](ql::size index) const;

			QL_SOURCE data_point_info& back();
			QL_SOURCE const data_point_info& back() const;
			QL_SOURCE data_point_info& front();
			QL_SOURCE const data_point_info& front() const;

			QL_SOURCE std::vector<data_point_info>::iterator begin();
			QL_SOURCE std::vector<data_point_info>::const_iterator begin() const;
			QL_SOURCE std::vector<data_point_info>::const_iterator cbegin();

			QL_SOURCE std::vector<data_point_info>::iterator end();
			QL_SOURCE std::vector<data_point_info>::const_iterator end() const;
			QL_SOURCE std::vector<data_point_info>::const_iterator cend();

			interpolation_type interpolation = interpolation_type::cubic;
			ql::rgba color = ql::rgba::unset();
			ql::f64 thickness = ql::f64_min;
			ql::size interpolation_steps = ql::size_max;
			ql::vtext text;
			bool only_draw_if_close = true;

			std::vector<data_point_info> data;
		};

		struct standard_graph
		{
			template <typename T>
			void set_data(const std::vector<T>& data)
			{
				this->data.resize(data.size());
				for (ql::u32 i = 0u; i < data.size(); ++i)
				{
					this->data[i].data = static_cast<ql::f64>(data[i]);
					this->data[i].color = this->color;
					this->data[i].thickness = this->thickness;
				}
			}

			template <typename T>
			void set_data(const std::vector<T>& data, ql::rgba color, ql::f64 thickness)
			{
				this->color = color;
				this->thickness = thickness;
				this->set_data(data);
			}

			QL_SOURCE void add_data(ql::f64 data);
			QL_SOURCE void add_data(ql::f64 data, ql::rgba color);
			QL_SOURCE void add_data(ql::f64 data, ql::rgba color, ql::f64 thickness);

			QL_SOURCE ql::f64 get_percentage_height_at(ql::size index) const;
			QL_SOURCE std::pair<data_point, data_point> get_low_high() const;
			QL_SOURCE ql::size size() const;
			QL_SOURCE void clear();
			QL_SOURCE data_point& operator[](ql::size index);
			QL_SOURCE const data_point& operator[](ql::size index) const;

			QL_SOURCE data_point& back();
			QL_SOURCE const data_point& back() const;
			QL_SOURCE data_point& front();
			QL_SOURCE const data_point& front() const;

			QL_SOURCE std::vector<data_point>::iterator begin();
			QL_SOURCE std::vector<data_point>::const_iterator begin() const;
			QL_SOURCE std::vector<data_point>::const_iterator cbegin();

			QL_SOURCE std::vector<data_point>::iterator end();
			QL_SOURCE std::vector<data_point>::const_iterator end() const;
			QL_SOURCE std::vector<data_point>::const_iterator cend();

			interpolation_type interpolation = interpolation_type::cubic;
			ql::rgba color = ql::rgba::unset();
			ql::f64 thickness = ql::f64_min;
			ql::size interpolation_steps = ql::size_max;

			std::vector<data_point> data;
		};

		struct simple_graph
		{
			template <typename T>
			void set_data(const std::vector<T>& data)
			{
				this->data.resize(data.size());
				for (ql::u32 i = 0u; i < data.size(); ++i)
				{
					this->data[i].data = static_cast<ql::f64>(data[i]);
				}
			}

			template <typename T>
			void set_data(const std::vector<T>& data, ql::rgba color, ql::f64 thickness)
			{
				this->color = color;
				this->thickness = thickness;
				this->set_data(data);
			}

			QL_SOURCE void add_data(ql::f64 data);

			QL_SOURCE ql::f64 get_percentage_height_at(ql::size index) const;
			QL_SOURCE std::pair<data_point_simple, data_point_simple> get_low_high() const;
			QL_SOURCE ql::size size() const;
			QL_SOURCE void clear();
			QL_SOURCE data_point_simple& operator[](ql::size index);
			QL_SOURCE const data_point_simple& operator[](ql::size index) const;

			QL_SOURCE data_point_simple& back();
			QL_SOURCE const data_point_simple& back() const;
			QL_SOURCE data_point_simple& front();
			QL_SOURCE const data_point_simple& front() const;

			QL_SOURCE std::vector<data_point_simple>::iterator begin();
			QL_SOURCE std::vector<data_point_simple>::const_iterator begin() const;
			QL_SOURCE std::vector<data_point_simple>::const_iterator cbegin();

			QL_SOURCE std::vector<data_point_simple>::iterator end();
			QL_SOURCE std::vector<data_point_simple>::const_iterator end() const;
			QL_SOURCE std::vector<data_point_simple>::const_iterator cend();

			interpolation_type interpolation = interpolation_type::cubic;
			ql::rgba color = ql::rgba::unset();
			ql::f64 thickness = ql::f64_min;
			ql::size interpolation_steps = ql::size_max;

			std::vector<data_point_simple> data;
		};

		bool drag = false;
		ql::vec2 click_position;

		QL_SOURCE void clear_data();
		QL_SOURCE bool empty() const;
		QL_SOURCE bool changed() const;
		QL_SOURCE void update_change() const;
		QL_SOURCE void check_x_axis() const;
		QL_SOURCE void enable_track_new_entries();
		QL_SOURCE void disable_track_new_entries();
		QL_SOURCE void enable_axis_info();
		QL_SOURCE void update(const event& event);
		QL_SOURCE void copy_visible_range(const vgraph& other);
		QL_SOURCE void set_visible_range(ql::size begin, ql::size end);
		QL_SOURCE void set_visible_range_max();

		QL_SOURCE void set_font(std::string name);
		QL_SOURCE std::string get_font() const;
		QL_SOURCE void set_dimension(ql::vec2 dimension);
		QL_SOURCE void set_position(ql::vec2 position);

		QL_SOURCE ql::f64 true_graph_width() const;
		QL_SOURCE ql::f64 true_graph_height() const;
		QL_SOURCE ql::vec2 true_graph_dimension() const;

		QL_SOURCE std::pair<ql::f64, ql::f64> get_low_high() const;
		QL_SOURCE ql::size total_graph_size() const;
		QL_SOURCE ql::size graph_element_size() const;
		QL_SOURCE ql::size visible_element_size() const;
		QL_SOURCE ql::size visible_index_start() const;
		QL_SOURCE ql::size visible_index_end() const;
		QL_SOURCE std::pair<ql::size, ql::size> visible_index_range() const;
		QL_SOURCE bool is_range_enabled() const;

		QL_SOURCE void add_info_graph(std::string name);
		QL_SOURCE info_graph& get_info_graph(std::string name);
		QL_SOURCE const info_graph& get_info_graph(std::string name) const;
		QL_SOURCE std::span<const data_point_info> get_info_graph_span(std::string name) const;

		QL_SOURCE void add_standard_graph(std::string name);
		QL_SOURCE standard_graph& get_standard_graph(std::string name);
		QL_SOURCE const standard_graph& get_standard_graph(std::string name) const;
		QL_SOURCE std::span<const data_point> get_standard_graph_span(std::string name) const;

		QL_SOURCE void add_simple_graph(std::string name);
		QL_SOURCE simple_graph& get_simple_graph(std::string name);
		QL_SOURCE const simple_graph& get_simple_graph(std::string name) const;
		QL_SOURCE std::span<const data_point_simple> get_simple_graph_span(std::string name) const;

		QL_SOURCE void add_y_axis_line(ql::f64 value);
		QL_SOURCE void add_y_axis_line(ql::f64 value, ql::rgba color, ql::f64 thickness = 2.0, bool foreground = true);
		QL_SOURCE highlighted_line& get_y_axis_line(ql::f64 value);
		QL_SOURCE const highlighted_line& get_y_axis_line(ql::f64 value) const;

		std::unordered_map<std::string, info_graph> info_graphs;
		std::unordered_map<std::string, standard_graph> standard_graphs;
		std::unordered_map<std::string, simple_graph> simple_graphs;

		std::unordered_map<ql::f64, highlighted_line> y_axis_highlighted_lines;

		ql::rgba background_color = ql::rgba::black();
	};

	struct graph
	{
		QL_SOURCE void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
		QL_SOURCE ql::graph& operator=(const ql::vgraph& graph);

		std::vector<std::vector<ql::text>> circle_texts;
		std::vector<ql::circles> circles;
		std::vector<ql::thick_lines> y_lines;
		std::vector<ql::thick_lines> y_lines_foreground;
		std::vector<ql::text> y_texts;
		std::vector<ql::thick_lines> x_lines;
		std::vector<ql::text> x_texts;

		std::vector<ql::thick_lines> lines;

		ql::text cursor_graph_text;
		ql::rectangle cursor_graph_background;

		ql::rectangle background;
	};

	struct border_graphic
	{
		const sf::Texture* texture;
		ql::vec2 texture_dimension;
		ql::vec2 dimension;
		ql::vec2 position;
		ql::vec2 scale = {1, 1};
		ql::rgba color;
		std::vector<ql::sprite> sprites;

		QL_SOURCE void set_dimension(ql::vec2 dimension);
		QL_SOURCE void set_position(ql::vec2 dimension);
		QL_SOURCE void increase(ql::vec2 increase);
		QL_SOURCE void set_color(ql::rgba color);
		QL_SOURCE void set_scale(ql::vec2 scale);
		QL_SOURCE void set_scale(ql::f32 scale);
		QL_SOURCE void set_texture(const sf::Texture& texture);
		QL_SOURCE void check_texture();
		QL_SOURCE void update_dimensions(ql::vec2 position, ql::vec2 dimension);
		QL_SOURCE void move(ql::vec2 delta);
		QL_SOURCE void clear();
		QL_SOURCE void add_top(ql::f32 correction_gap = 0.0f);
		QL_SOURCE void add_bottom(ql::f32 correction_gap = 0.0f);
		QL_SOURCE void add_left(ql::f32 correction_gap = 0.0f);
		QL_SOURCE void add_right(ql::f32 correction_gap = 0.0f);
		QL_SOURCE void add_all_sides(ql::f32 correction_gap = 0.0f);
		QL_SOURCE void draw(ql::render& object) const;
	};

	struct glyph_quad_vertex
	{
		ql::vec2f position;
		ql::vec2f tex_coord;
	};

	using glyph_quad = std::array<glyph_quad_vertex, 6u>;

	struct colored_text
	{
		colored_text();
		colored_text(const colored_text&);
		colored_text& operator=(const colored_text&);
		colored_text(colored_text&&) noexcept;
		colored_text& operator=(colored_text&&) noexcept;

		QL_SOURCE void set_font(const sf::Font& font);
		QL_SOURCE void set_unicode_font(const sf::Font& font);
		QL_SOURCE void set_font(sf::Font&& font) = delete;
		QL_SOURCE void set_character_size(ql::u32 size);
		QL_SOURCE void set_line_spacing(ql::f32 spacingFactor);
		QL_SOURCE void set_letter_spacing(ql::f32 spacingFactor);
		QL_SOURCE void set_style(ql::u32 style);
		QL_SOURCE ql::u32 get_character_size() const;
		QL_SOURCE ql::f32 get_line_spacing() const;
		QL_SOURCE ql::f32 get_line_spacing_pixels() const;
		QL_SOURCE ql::u32 get_style() const;
		QL_SOURCE ql::f32 get_outline_thickness() const;
		QL_SOURCE ql::f32 get_white_space_width() const;
		QL_SOURCE ql::f32 get_underline_position() const;
		QL_SOURCE ql::f32 get_chracter_top_offset() const;
		QL_SOURCE const sf::Glyph&
		get_glyph(ql::u32 character, ql::u32 character_size, bool is_bold, ql::f32 outline_thickness = 0.f);
		QL_SOURCE const sf::Glyph&
		get_unicode_glyph(ql::u32 character, ql::u32 character_size, bool is_bold, ql::f32 outline_thickness = 0.f);

		QL_SOURCE void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		QL_SOURCE void
		add(const ql::styled_string<std::u32string>& string, ql::f32 visible_y_min = ql::f32_min, ql::f32 visible_y_max = ql::f32_max
		);
		QL_SOURCE void create(
				const ql::styled_string<std::u32string>& string,
				ql::f32 visible_y_min = ql::f32_min,
				ql::f32 visible_y_max = ql::f32_max
		);
		QL_SOURCE void clear();

		QL_SOURCE void pop_last_character();

		template <typename T>
		colored_text& operator<<(const T& value)
		{
			ql::styled_string<std::u32string> string;
			string.clear_copy_style(this->last_element);
			string.elements[0u].text = ql::to_basic_string<char32_t>(value);
			this->add(string);
			return *this;
		}

		const sf::Font* font = nullptr;
		const sf::Font* unicode_font = nullptr;
		ql::styled_string<std::u32string>::element last_element;
		ql::u32 character_size{30};
		ql::f32 letter_spacing_factor{1.f};
		ql::f32 line_spacing_factor{1.f};
		ql::u32 style{sf::Text::Style::Regular};
		ql::rgba fill_color{ql::rgba::white()};
		ql::rgba outline_color{ql::rgba::black()};
		ql::f32 outline_thickness{0.f};
		ql::vertex_array vertices{sf::PrimitiveType::Triangles};
		ql::vertex_array outline_vertices{sf::PrimitiveType::Triangles};
		ql::vertex_array unicode_vertices{sf::PrimitiveType::Triangles};
		ql::vertex_array unicode_outline_vertices{sf::PrimitiveType::Triangles};
		ql::hitbox hitbox;
		ql::vec2f text_position;
		ql::size rows = 0u;
	};

	namespace detail
	{
		QL_SOURCE extern std::unordered_map<std::string, ql::text> texts;
	}

	QL_SOURCE ql::text& get_text(const std::string& name = "QL_DEFAULT");
	QL_SOURCE void add_text(const std::string& name = "QL_DEFAULT");

}	 // namespace ql

#endif