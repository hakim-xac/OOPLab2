#ifndef Rectangle__
#define Rectange__

#include <Windows.h>
#include "Line.h"
#include "Enums.h"

namespace KHAS {

	class MyRectangle : public Line
	{
	private:

		int right_point_;
		int bottom_point_;

	public:
		MyRectangle() = delete;
		MyRectangle(const RECT& rect);

		int getRightPointX() const;
		int getBottomPointY() const;

		void setRightPointX(int value);
		void setBottomPointY(int value);

		static void draw(const HDC& hdc, const MyRectangle& rectangle);
		void moveRandom();
		void move(MoveDirection md);
	};

}
#endif