#include "Rectangle.h"
#include <random>

namespace KHAS {

	MyRectangle::MyRectangle(const RECT& rect)
		: Line(rect)
		, right_point_()
		, bottom_point_()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		auto x{ getX() };
		auto y{ getY() };
		std::uniform_int_distribution dist_right_point(x + 10, x + 100);
		std::uniform_int_distribution dist_bottom_point(y + 10, y + 100);


		right_point_ = dist_right_point(gen);
		bottom_point_ = dist_bottom_point(gen);
	}

	int MyRectangle::getRightPointX() const
	{
		return right_point_;
	}

	int MyRectangle::getBottomPointY() const
	{
		return bottom_point_;
	}

	void MyRectangle::setRightPointX(int value)
	{
		right_point_ = value;
	}

	void MyRectangle::setBottomPointY(int value)
	{
		bottom_point_ = value;
	}

	void MyRectangle::draw(const HDC& hdc, const MyRectangle& rectangle)
	{
		HBRUSH solid_brush{ CreateSolidBrush(rectangle.getColor()) };
		SelectObject(hdc, solid_brush);
		Rectangle(hdc, rectangle.getX(), rectangle.getY(), rectangle.getRightPointX(), rectangle.getBottomPointY());
		DeleteObject(solid_brush);
	}

	void MyRectangle::moveRandom(MyRectangle& object)
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

	void MyRectangle::move(MoveDirection md, MyRectangle& object)
	{
		switch (md)
		{
		case KHAS::MoveDirection::Up:
			object.setY(object.getY() - 1);
			object.setBottomPointY(object.getBottomPointY() - 1);
			break;
		case KHAS::MoveDirection::Right:
			object.setX(object.getX() + 1);
			object.setRightPointX(object.getRightPointX() + 1);
			break;
		case KHAS::MoveDirection::Down:
			object.setY(object.getY() + 1);
			object.setBottomPointY(object.getBottomPointY() + 1);
			break;
		case KHAS::MoveDirection::Left:
			object.setX(object.getX() - 1);
			object.setRightPointX(object.getRightPointX() - 1);
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