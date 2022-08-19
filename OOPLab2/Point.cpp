#include "Point.h"
#include "Funcions.h"
#include <random>


namespace KHAS {

    Point::Point(const RECT& rect)
        :pos_x_()
        , pos_y_()
        , max_rect_(rect)
        , color_()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution dist_lr(static_cast<int>(max_rect_.left), static_cast<int>(max_rect_.right));
        std::uniform_int_distribution dist_tb(static_cast<int>(max_rect_.top), static_cast<int>(max_rect_.bottom));
        std::uniform_int_distribution dist_color(0, 255);

        pos_x_ = dist_lr(gen);
        pos_y_ = dist_tb(gen);
        color_ = Functions::rgbToCOLORREF(dist_color(gen), dist_color(gen), dist_color(gen));
    }

    int Point::getX() const
    {
        return pos_x_;
    }

    int Point::getY() const
    {
        return pos_y_;
    }

    const COLORREF& Point::getColor() const
    {
        return color_;
    }

    void Point::setX(int value)
    {
        pos_x_ = value;
    }

    void Point::setY(int value)
    {
        pos_y_ = value;
    }

    void Point::setColor(const COLORREF& color)
    {
        color_ = color;
    }

    void Point::draw(const HDC& hdc, const Point& point)
    {
        SetPixel(hdc, point.getX() + 1, point.getY(), point.getColor());
        SetPixel(hdc, point.getX() - 1, point.getY(), point.getColor());
        SetPixel(hdc, point.getX() + 1, point.getY() + 1, point.getColor());
        SetPixel(hdc, point.getX() - 1, point.getY() - 1, point.getColor());
        SetPixel(hdc, point.getX(), point.getY() + 1, point.getColor());
        SetPixel(hdc, point.getX(), point.getY() - 1, point.getColor());
        SetPixel(hdc, point.getX() + 1, point.getY() - 1, point.getColor());
        SetPixel(hdc, point.getX() - 1, point.getY() + 1, point.getColor());
        SetPixel(hdc, point.getX(), point.getY(), point.getColor());
    }

    void Point::moveRandom(Point& object)
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
        default:                                break;
        }
    }

    void Point::move(MoveDirection md, Point& object)
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