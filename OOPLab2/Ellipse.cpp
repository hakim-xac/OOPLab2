#include "Ellipse.h"
#include <random>

namespace KHAS {

	MyEllipse::MyEllipse(const RECT& rect)
	: Circle(rect)
	, height_radius_() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution dist_height_radius(10, 100);
		height_radius_ = dist_height_radius(gen);
	}

	int MyEllipse::getHeightRadius() const
	{
		return height_radius_;
	}

	void MyEllipse::setBigRadius(int new_height_radius)
	{
		height_radius_ = new_height_radius;
	}

	void MyEllipse::draw(const HDC& hdc, const MyEllipse& ellipse)
	{
		HBRUSH brush_solid{ CreateSolidBrush(ellipse.getColor()) };
		SelectObject(hdc, brush_solid);

		auto x{ ellipse.getX() };
		auto y{ ellipse.getY() };
		auto width_radius{ ellipse.getRadius() };
		auto height_radius{ ellipse.getHeightRadius() };

		Ellipse(hdc, x, y, x + width_radius, y + height_radius);

		DeleteObject(brush_solid);
	}

    void MyEllipse::moveRandom(MyEllipse& object)
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

    void MyEllipse::move(MoveDirection md, MyEllipse& object)
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