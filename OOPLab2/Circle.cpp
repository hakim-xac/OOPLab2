#include "Circle.h"
#include <random>


namespace KHAS {


	Circle::Circle(const RECT& rect)
        : Point(rect)
        , radius_()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution dist_radius(10, 100);        
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

    void Circle::draw(const HDC& hdc, const Circle& circle)
    {
        HBRUSH brush_solid{ CreateSolidBrush(circle.getColor()) };
        SelectObject(hdc, brush_solid);
        auto x{ circle.getX() };
        auto y{ circle.getY() };
        auto radius{ circle.getRadius() };
        Ellipse(hdc, x, y, x + radius, y + radius);
        DeleteObject(brush_solid);
    }


}