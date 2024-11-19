#include <ql/graphic/drawable/advanced/polygon/polygon.hpp>

#if defined QL_GRAPHIC

namespace ql
{
	sf::Vector2f ql::polygon_shape::polygon_proxy::operator=(ql::vec2 position)
	{
		this->ptr->setPoint(this->index, position);
		return this->ptr->getPoint(this->index);
	}

	ql::polygon_shape::polygon_proxy::operator ql::vec2() const
	{
		return this->ptr->getPoint(this->index);
	}

	ql::polygon_shape::const_polygon_proxy::operator ql::vec2() const
	{
		return this->ptr->getPoint(this->index);
	}

	ql::polygon_shape::polygon_proxy ql::polygon_shape::operator[](ql::size index)
	{
		ql::polygon_shape::polygon_proxy result;
		result.ptr = &this->shape;
		result.index = index;
		return result;
	}

	ql::polygon_shape::const_polygon_proxy ql::polygon_shape::operator[](ql::size index) const
	{
		ql::polygon_shape::const_polygon_proxy result;
		result.ptr = &this->shape;
		result.index = index;
		return result;
	}

	ql::polygon_shape::polygon_proxy ql::polygon_shape::front()
	{
		ql::polygon_shape::polygon_proxy result;
		result.ptr = &this->shape;
		result.index = 0u;
		return result;
	}

	ql::polygon_shape::const_polygon_proxy ql::polygon_shape::front() const
	{
		ql::polygon_shape::const_polygon_proxy result;
		result.ptr = &this->shape;
		result.index = 0u;
		return result;
	}

	ql::polygon_shape::polygon_proxy ql::polygon_shape::back()
	{
		ql::polygon_shape::polygon_proxy result;
		result.ptr = &this->shape;
		result.index = this->size() - 1;
		return result;
	}

	ql::polygon_shape::const_polygon_proxy ql::polygon_shape::back() const
	{
		ql::polygon_shape::const_polygon_proxy result;
		result.ptr = &this->shape;
		result.index = 0u;
		return result;
	}

	void ql::polygon_shape::set_outline_thickness(ql::f32 thickness)
	{
		this->shape.setOutlineThickness(thickness);
	}

	void ql::polygon_shape::set_outline_color(ql::rgba color)
	{
		this->shape.setOutlineColor(color);
	}

	void ql::polygon_shape::set_color(ql::rgba color)
	{
		this->shape.setFillColor(color);
	}

	void ql::polygon_shape::set_position(ql::vec2 position)
	{
		this->shape.setPosition(position);
	}

	ql::f32 ql::polygon_shape::get_outline_thickness() const
	{
		return this->shape.getOutlineThickness();
	}

	ql::rgba ql::polygon_shape::get_outline_color() const
	{
		return this->shape.getOutlineColor();
	}

	ql::rgba ql::polygon_shape::get_color() const
	{
		return this->shape.getFillColor();
	}

	void ql::polygon_shape::move(ql::vec2 delta)
	{
		this->shape.move(delta);
	}

	void ql::polygon_shape::set_point(ql::size index, ql::vec2 position)
	{
		this->shape.setPoint(index, position);
	}

	ql::vec2 ql::polygon_shape::get_point(ql::size index) const
	{
		return this->shape.getPoint(index);
	}

	ql::size ql::polygon_shape::size() const
	{
		return this->shape.getPointCount();
	}

	void ql::polygon_shape::resize(ql::size size)
	{
		this->shape.setPointCount(size);
	}

	bool ql::polygon_shape::collides(ql::vec2 point, ql::size increment) const
	{
		bool flag = false;

		ql::straight_line compare;
		compare.a = {0, 0};
		compare.b = point;

		auto j = this->size() - 1;
		for (ql::size i = 0u; i < this->size(); i += increment)
		{
			ql::straight_line edge_line;
			edge_line.a = this->get_point(i);
			edge_line.b = this->get_point(j);
			if (compare.collides(edge_line))
			{
				flag = !flag;
			}
			j = i;
		}
		return flag;
	}

	void ql::polygon_shape::draw(sf::RenderTarget& window, sf::RenderStates states) const
	{
		window.draw(this->shape, states);
	}

}	 // namespace ql

#endif