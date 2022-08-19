#include "Line.h"
#include <random>

namespace KHAS {
    Line::Line(const RECT& rect)
        : Point(rect)
        , second_point_pos_x_()
        , second_point_pos_y_()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        auto x{ getX() };
        auto y{ getY() };
        std::uniform_int_distribution dist_second_pos_x(x, x + 200);
        std::uniform_int_distribution dist_second_pos_y(y, y + 200);


        second_point_pos_x_ = dist_second_pos_x(gen);
        second_point_pos_y_ = dist_second_pos_y(gen);
    }

    int Line::getSecondPosX() const
    {
        return second_point_pos_x_;
    }

    int Line::getSecondPosY() const
    {
        return second_point_pos_y_;
    }

    void Line::setSecondPosX(int value)
    {
        second_point_pos_x_ = value;
    }

    void Line::setSecondPosY(int value)
    {
        second_point_pos_y_ = value;
    }

    void Line::move(MoveDirection md, Line& object)
    {
        switch (md)
        {
        case KHAS::MoveDirection::Up:
            object.setY(object.getY() - 1);
            object.setSecondPosY(object.getSecondPosY() - 1);
            break;
        case KHAS::MoveDirection::Right:
            object.setX(object.getX() + 1);
            object.setSecondPosX(object.getSecondPosX() + 1);
            break;
        case KHAS::MoveDirection::Down:
            object.setY(object.getY() + 1);
            object.setSecondPosY(object.getSecondPosY() + 1);
            break;
        case KHAS::MoveDirection::Left:
            object.setX(object.getX() - 1);
            object.setSecondPosX(object.getSecondPosX() - 1);
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

    void Line::moveRandom(Line& object)
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
        default:										break;
        }
    }

    void Line::draw(const HDC& hdc, const Line& line)
    {
        HPEN line_pen{ CreatePen(PS_SOLID, 1, line.getColor()) };
        SelectObject(hdc, line_pen);
        MoveToEx(hdc, line.getX(), line.getY(), NULL);

        LineTo(hdc, line.getSecondPosX(), line.getSecondPosY());

        DeleteObject(line_pen);
    }



}