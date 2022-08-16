#ifndef Point__
#define Point__

#include <Windows.h>
#include "Enums.h"

namespace KHAS {
	class Point
	{
	private:

		int pos_x_;
		int pos_y_;
		RECT max_rect_;
		COLORREF color_;

	public:
		Point() = delete;
		Point(const RECT& recr);

		int getX() const;
		int getY() const;
		COLORREF getColor() const;

		void setX(int value);
		void setY(int value);
		void setColor(const COLORREF& color);

		void draw(const HDC& hdc) const;
		void move(MoveDirection md);
		void moveRandom();

	};

	class Circle {
	private:
		int pos_x_;
		int pos_y_;
		int radius_;
		COLORREF color_;
	public:
		int getX() const { return pos_x_;  };

	};
}


#endif