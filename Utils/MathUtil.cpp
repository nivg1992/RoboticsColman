#include "MathUtil.h"

namespace Utils {

bool MathUtil::inRange(double num, double rangeStart, double rangeEnd,
		bool inclusive) {
	if (inclusive) {
		return num >= rangeStart && num <= rangeEnd;
	} else {
		return num > rangeStart && num < rangeEnd;
	}
}

double MathUtil::distance(double deltaX, double deltaY) {
	return sqrt(pow(deltaX, 2) + pow(deltaY, 2));
}

double MathUtil::distance(double x1, double y1, double x2, double y2) {
	return distance(x2 - x1, y2 - y1);
}

double MathUtil::normalize(double num, double min, double max) {
	if (inRange(num, min, max)) {
		return num;
	} else if (num < min) {
		return min;
	} else if (num > max) {
		return max;
	}

	return NAN;
}

bool MathUtil::equals(double number, double comparee, double epsilon) {
	return inRange(number, comparee - epsilon, comparee + epsilon);
}

float MathUtil::incline(double x1, double y1, double x2, double y2) {
	float dY = (signed) (y1 - y2);
	float dX = (signed) (x1 - x2);

	if (x1 == x2)
		return FLT_MAX;
	else
		return fabs(dY / dX);
}
}

