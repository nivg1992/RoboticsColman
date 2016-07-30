#pragma once

#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>
#include "Consts.h"
#include "Utils/MathUtil.h"
#include "Models/Location.h"
#include "Models/AnotherMap.h"

using namespace std;
using namespace PlayerCc;
using namespace Consts;

class Robot {
	PlayerClient*_pc;
	Position2dProxy* _pp;

public:
	LaserProxy* _lp;
	double odX;
	double odY;
	double odYaw;
	Robot(char* ip, int port);
	void Read() {
		// TODO
		_pc->Read();
	}
	void setOdemetry(double x, double y, double yaw) {
		odX = x;
		odY = y;
		odYaw = yaw;
		this->_pp->SetOdometry(x,
				y, yaw);
	}
	void setSpeed(float xSpeed, float angularSpeed) {
		// TODO: check if we need to do:  cm_to_m to the x speed! we need.
		// TODO: need to check if do it here or in the caller method

		_pp->SetSpeed(xSpeed, angularSpeed);
	}
	void kickstart() {
		//For fixing Player's reading BUG
		for (int i = 0; i < 30; i++) {
			Read();
			setOdemetry(odX, odY, odYaw);
		}

	}

	Location getLocation();
	bool canMoveForward();
	float* getAllLasers() {
		unsigned count = this->_lp->GetCount();
		float* lasers = new float[count];
		for (unsigned i = 0; i < count; i++) {
			lasers[i] = this->_lp->GetRange(i);
		}
		return lasers;
	}
	void setLocation(double x, double y, double yaw) {
		this->robot_XPos = x;
		this->robot_YPos = y;
		this->robot_Yaw = yaw;
	}
	bool canTurnRight();
	bool canTurnLeft();

	void calcLocationDeltas(double &DelX, double &DelY, double &DelYaw, AnotherMap* map);
	double getDistanceFromObstacle(int index);
	double getXPosition();
	double getYPosition();
	double getYawPosition();

	double getRangeLaser(unsigned index);
	double getRangeLaser(double angle);
	double getRaysRangeSum(double rangeStartAngle, double rangeEndAngle);

	virtual ~Robot();

protected:
	static double indexToAngle(int index);
	static unsigned angleToIndex(double angle);
	static double convertDegreesToRadians(double deg);
	bool canTurnInDirection(double startRangeAngle, double endRangeAngle);

	double robot_XPos;
	double robot_YPos;
	double robot_Yaw;
};

#endif /* ROBOT_H_ */
