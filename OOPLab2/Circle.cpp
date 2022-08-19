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

    void Circle::moveRandom(Circle& object)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution dist_move_direction(0, 7);

        auto move_random{ dist_move_direction(gen) };

        switch (move_random)
        {
        case 0: move(MoveDirection::Up, object);        break;
        case 1: move(MoveDirection::UpRight, object);   break;
        case 2: move(MoveDirection::Right, object);     break;
        case 3: move(MoveDirection::DownRight, object); break;
        case 4: move(MoveDirection::Down, object);      break;
        case 5: move(MoveDirection::DownLeft, object);  break;
        case 6: move(MoveDirection::Left, object);      break;
        case 7: move(MoveDirection::UpLeft, object);    break;
        default:                                        break;
        }
    }

    void Circle::move(MoveDirection md, Circle& object)
    {
        switch (md)
        {
        case KHAS::MoveDirection::Up:
            object.setY(object.getY() - 1);
            break;
        case KHAS::MoveDirection::Right:
            object.setX(object.getX() + 1);
            break;
        case KHAS::MoveDirection::Down:
            object.setY(object.getY() + 1);
            break;
        case KHAS::MoveDirection::Left:
            object.setX(object.getX() - 1);
            break;
        case KHAS::MoveDirection::UpRight:
            move(MoveDirection::Up, object);
            move(MoveDirection::Right, object);
            break;
        case KHAS::MoveDirection::UpLeft:
            move(MoveDirection::Up, object);
            move(MoveDirection::Left, object);
            break;
        case KHAS::MoveDirection::DownRight:
            move(MoveDirection::Down, object);
            move(MoveDirection::Right, object);
            break;
        case KHAS::MoveDirection::DownLeft:
            move(MoveDirection::Down, object);
            move(MoveDirection::Left, object);
            break;
        case KHAS::MoveDirection::Empty:
            break;
        default:
            break;
        }
    }


}