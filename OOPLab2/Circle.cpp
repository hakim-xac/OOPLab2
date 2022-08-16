#include "Circle.h"
#include <random>


namespace KHAS {


	Circle::Circle(const RECT& rect)
        : Point(rect)
        , radius_()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution dist_radius(5, 20);        
        radius_ = dist_radius(gen);
    }

    int Circle::getRadius() const
    {
        return radius_;
    }

    void Circle::setRadius(int new_radius)
    {
        radius_ = new_radius;
    }

    void Circle::draw(const HDC& hdc) const
    {
        HBRUSH brush_solid{ CreateSolidBrush(getColor()) };
        SelectObject(hdc, brush_solid);
        Ellipse(hdc, getX(), getY(), getX() + radius_, getY() + radius_);
        DeleteObject(brush_solid);
    }


}