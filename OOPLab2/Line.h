#ifndef Line__
#define Line__

#include <Windows.h>
#include "Point.h"
#include "Enums.h"

namespace KHAS {
	class Line : public Point
	{
	private:

		int end_pos_x_;
		int end_pos_y_;

	public:
		Line() = delete;
		Line(const RECT& rect);

		int getEndPosX() const;
		int getEndPosY() const;

		void setEndPosX(int value);
		void setEndPosY(int value);


		void move(MoveDirection md); 
		void moveRandom();
		void draw(const HDC& hdc) const;
	};
}


#endif