#ifndef Line__
#define Line__

#include <Windows.h>
#include "Point.h"
#include "Enums.h"

namespace KHAS {
	class Line : public Point
	{
	private:

		int second_point_pos_x_;
		int second_point_pos_y_;

	public:
		Line() = delete;
		Line(const RECT& rect);

		int getSecondPosX() const;
		int getSecondPosY() const;

		void setSecondPosX(int value);
		void setSecondPosY(int value);


		void move(MoveDirection md); 
		void moveRandom();
		static void draw(const HDC& hdc, const Line& line);
	};
}


#endif