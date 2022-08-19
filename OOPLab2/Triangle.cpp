#include "Triangle.h"
#include <random>

namespace KHAS {

	Triangle::Triangle(const RECT& rect)
		: Line(rect)
		, third_point_pos_x_()
		, third_point_pos_y_()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution dist_third_pos_x(getX(), getSecondPosX());
		std::uniform_int_distribution dist_third_pos_y(getY(), getSecondPosY());


		third_point_pos_x_ = dist_third_pos_x(gen);
		third_point_pos_y_ = dist_third_pos_y(gen);
	}

	int Triangle::getThirdPosX() const
	{
		return third_point_pos_x_;
	}

	int Triangle::getThirdPosY() const
	{
		return third_point_pos_y_;
	}

	void Triangle::setThirdPosX(int value)
	{
		third_point_pos_x_ = value;
	}

	void Triangle::setThirdPosY(int value)
	{
		third_point_pos_y_ = value;
	}

	void Triangle::move(MoveDirection md, Triangle& object)
	{
		switch (md)
		{
		case KHAS::MoveDirection::Up:
			object.setY(object.getY() - 1);
			object.setSecondPosY(object.getSecondPosY() - 1);
			object.setThirdPosY(object.getThirdPosY() - 1);
			break;
		case KHAS::MoveDirection::Right:
			object.setX(object.getX() + 1);
			object.setSecondPosX(object.getSecondPosX() + 1);
			object.setThirdPosX(object.getThirdPosX() + 1);
			break;
		case KHAS::MoveDirection::Down:
			object.setY(object.getY() + 1);
			object.setSecondPosY(object.getSecondPosY() + 1);
			object.setThirdPosY(object.getThirdPosY() + 1);
			break;
		case KHAS::MoveDirection::Left:
			object.setX(object.getX() - 1);
			object.setSecondPosX(object.getSecondPosX() - 1);
			object.setThirdPosX(object.getThirdPosX() - 1);
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

	void Triangle::moveRandom(Triangle& object)
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

	void Triangle::draw(const HDC& hdc, const Triangle& triangle)
	{
		POINT array_triangle_points[]{
			POINT{ triangle.getX(), triangle.getY() }
			, POINT{ triangle.getSecondPosX(), triangle.getSecondPosY() }
			, POINT{ triangle.getThirdPosX(), triangle.getThirdPosY() }
		};
		HBRUSH solidBrush{ CreateSolidBrush(triangle.getColor()) };
		HRGN hrgn{ CreatePolygonRgn(array_triangle_points, sizeof(array_triangle_points) / sizeof(POINT), ALTERNATE)};
		SelectObject(hdc, solidBrush);

		FillRgn(hdc,hrgn, solidBrush);

		DeleteObject(hrgn);
		DeleteObject(solidBrush);
	}
}