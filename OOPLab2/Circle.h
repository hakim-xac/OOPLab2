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
		void draw(const HDC& hdc) const;
	};

}

#endif

