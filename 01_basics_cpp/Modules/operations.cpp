#include "operations.h"

#define _USE_MATH_DEFINES
#include <cmath>

namespace Rectangle {
	float area(float length, float width) {
		return length * width;
	}
	float perimeter(float length, float width) {
		return length * 2 + width * 2;
	}
}

namespace Circle {
	float circumference(float radius) {
		return 2 * M_PI * radius;
	}
	float area(float radius) {
		return M_PI * radius * radius;
	}
}