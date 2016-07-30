#pragma once

#include <math.h>
#include <float.h>
#include "../Managers/ConfigurationManager.h"

namespace Utils {

#define degToRad(angDeg) (angDeg * M_PI / 180.0)
#define radToDeg(angRad) (angRad * 180.0 / M_PI)

#define m_to_cm(m) (m * 100)
#define cm_to_m(cm) (0.01 * cm)

	class MathUtil {
		public:

			static unsigned cmToPx(float cm) {
				return cm / Managers::ConfigurationManager::GetInstance()->getPngGridResolution();
			}

			static float pxToCm(unsigned px) {
				return px * Managers::ConfigurationManager::GetInstance()->getPngGridResolution();
			}

			static bool inRange(double num, double rangeStart, double rangeEnd, bool inclusive = true);
			static double distance(double deltaX, double deltaY);
			static double distance(double x1, double y1, double x2, double y2);
			static double normalize(double num, double min = DBL_MIN, double max = DBL_MAX);
			static bool equals(double number, double compare, double epsilon = DBL_EPSILON);
			static float incline(double x1, double y1, double x2, double y2);

		//	static double convertDegreesToRadians(double deg);

	};

}
