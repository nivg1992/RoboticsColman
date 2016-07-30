#include "Robot.h"
#include <stdexcept>

Robot::Robot(char* ip, int port) {

	_pc = new PlayerClient(ip, port);
	_pp = new Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);

	_pp->SetMotorEnable(true);

	robot_XPos = 0;
	robot_YPos = 0;
	robot_Yaw = 0;
}

Location Robot::getLocation() {
	return Location(this->getXPosition(), this->getYPosition(), this->getYawPosition());
}

double Robot::getXPosition() {
	return _pp->GetXPos();
}

double Robot::getYPosition() {
	return _pp->GetYPos();
}

double Robot::getYawPosition() {
	return _pp->GetYaw();
}

void Robot::calcLocationDeltas(double &DelX, double &DelY, double &DelYaw, AnotherMap* map) {
	// Getting the new position of the robot
	double currRobotX = Utils::MathUtil::cmToPx(_pp->GetXPos() * 100);
	double currRobotY = Utils::MathUtil::cmToPx(_pp->GetYPos() * 100);

	// Getting the robot yaw and casting it from radians to degrees
	double x = _pp->GetYaw();
	double currRobotYaw = x * 180 / M_PI;

	// Calculating the deltas
	DelX = currRobotX - robot_XPos;
	DelY = currRobotY - robot_YPos;
	DelYaw = fmod(currRobotYaw - robot_Yaw, 360);

	// Updating the robot location
	robot_XPos = currRobotX;
	robot_YPos = currRobotY;
	robot_Yaw = currRobotYaw;
}

bool Robot::canTurnRight() {
	return canTurnInDirection(START_RIGHT_RAYS_RANGE_ANGLE,
			END_RIGHT_RAYS_RANGE_ANGLE);
}

bool Robot::canTurnLeft() {
	return canTurnInDirection(START_LEFT_RAYS_RANGE_ANGLE,
			END_LEFT_RAYS_RANGE_ANGLE);
}

bool Robot::canTurnInDirection(double startRangeAngle, double endRangeAngle) {
	int rangeStartIndex = angleToIndex(startRangeAngle);
	int rangeEndIndex = angleToIndex(endRangeAngle);

	for (int i = rangeStartIndex; i < rangeEndIndex; i++) {
		if (getDistanceFromObstacle(i) <= 0.4) {
			return false;
		}
	}

	return true;
}

bool Robot::canMoveForward() {
	double dis;
	int rightCorner = angleToIndex(-30);
	int leftCorner = angleToIndex(30);
	for (int i = rightCorner; i <= leftCorner; i++) {
		dis = getDistanceFromObstacle(i);
		if (dis <= 0.7) {
			return false;
		}
	}
	return true;
}

// This function summarize the "rays range" distances from obstacles
double Robot::getRaysRangeSum(double rangeStartAngle, double rangeEndAngle) {
	double sum = 0;

	int rangeStartIndex = angleToIndex(rangeStartAngle);
	int rangeEndIndex = angleToIndex(rangeEndAngle);

	for (int i = rangeStartIndex; i <= rangeEndIndex; i++) {
		sum += getDistanceFromObstacle(i);
	}

	return sum;
}

double Robot::getRangeLaser(unsigned index) {
	if (index < 0 || index > LASER_SLEASER_ARRAY_SIZE) {
		return -1;
	}
	return _lp->GetRange(index);;
}

double Robot::getRangeLaser(double angle) {
	return getRangeLaser(angleToIndex(angle));
}

double Robot::indexToAngle(int index) {
	double angular_resolution = LASER_FOV_DEGREE
			/ (double) LASER_SLEASER_ARRAY_SIZE;
	double min_angle = LASER_FOV_DEGREE / 2;

	double angle = index * angular_resolution - min_angle;
	return angle;
}

unsigned Robot::angleToIndex(double angle) {
	double min_angle = LASER_FOV_DEGREE / 2;

	int index = ((double) LASER_SLEASER_ARRAY_SIZE / LASER_FOV_DEGREE)
			* (angle + min_angle);
	if (index >= LASER_SLEASER_ARRAY_SIZE) {
		throw new out_of_range("index larger than possible.");
	}
	return index;
}

double Robot::getDistanceFromObstacle(int index) {
	return (*_lp)[index];
}

Robot::~Robot() {
	delete _pc;
	delete _pp;
	delete _lp;
}
