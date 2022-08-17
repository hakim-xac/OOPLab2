#ifndef Ellipse__
#define Ellipse__

#include <Windows.h>
#include "Circle.h"

namespace KHAS {
	class MyEllipse : public Circle
	{
	private:

		int height_radius_;

	public:
		MyEllipse() = delete;
		MyEllipse(const RECT& rect);

		int getHeightRadius() const;
		void setBigRadius(int new_height_radius);

		static void draw(const HDC& hdc, const MyEllipse& ellipse);
	};
}

#endif