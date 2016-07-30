#pragma once

#ifndef WAYPOINT_H_
#define WAYPOINT_H_
using namespace std;

class Waypoint {
public:
	Waypoint(double x, double y, double yaw) :
			m_X(x), m_Y(y), m_Yaw(yaw) {

	}

	Waypoint(Waypoint* waypoint) :
			m_X(waypoint->getX()), m_Y(waypoint->getY()), m_Yaw(
					waypoint->getYaw()) {

	}

	Waypoint()
	{

	}


	inline double getX() {
		return m_X;
	}
	;

	inline double getY() {
		return m_Y;
	}
	;

	inline double getYaw() {
		return m_Yaw;
	}
	;

private:
	double m_X;
	double m_Y;
	double m_Yaw;
};

#endif /* WAYPOINT_H_ */
