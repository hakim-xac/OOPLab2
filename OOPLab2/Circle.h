#ifndef Circle__
#define Circle__

#include <Windows.h>
#include "Enums.h"
#include "Point.h"

namespace KHAS {

	class Circle : public Point
	{
	private:

		int radius_;

	public:
		Circle() = delete;
		Circle(const RECT& rect);

		int getRadius() const;
		void setRadius(int new_radius);

		static void draw(const HDC& hdc, const Circle& circle);
		static void move(MoveDirection md, Circle& object);
		static void moveRandom(Circle& object);
	};

}

#endif

