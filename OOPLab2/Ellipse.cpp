#include "Ellipse.h"
#include <random>

namespace KHAS {

	MyEllipse::MyEllipse(const RECT& rect)
	: Circle(rect)
	, height_radius_() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution dist_height_radius(5, 20);
		height_radius_ = dist_height_radius(gen);
	}

	int MyEllipse::getBigRadius() const
	{
		return height_radius_;
	}

	void MyEllipse::setBigRadius(int new_height_radius)
	{
		height_radius_ = new_height_radius;
	}

	void MyEllipse::draw(const HDC& hdc) const
	{
		HBRUSH brush_solid{ CreateSolidBrush(getColor()) };
		SelectObject(hdc, brush_solid);
		Ellipse(hdc, getX(), getY(), getX() + getRadius(), getY() + height_radius_);
		DeleteObject(brush_solid);
	}

}