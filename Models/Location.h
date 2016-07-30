#pragma once

#ifndef LOCATION_H_
#define LOCATION_H_

class Location {
public:
	double m_X;
	double m_Y;
	double m_Yaw;
	Location();
	Location(double x, double y, double Yaw);
	virtual ~Location();

	inline unsigned getX() {
		return m_X;
	}
	;

	inline unsigned getY() {
		return m_Y;
	}
	;

	inline double getYaw() {
		return m_Yaw;
	}
	;

};

#endif /* LOCATION_H_ */
