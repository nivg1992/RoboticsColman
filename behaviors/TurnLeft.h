#ifndef TURNLEFT_H_
#define TURNLEFT_H_

#include "Behavior.h"
#include "../Consts.h"

class TurnLeft: public Behavior {
public:
	TurnLeft(Robot* robot);

	bool startCond() {
		return _robot->canTurnLeft();
	}

	bool stopCond() {
		return _robot->canMoveForward();
	}

	void action() {
		_robot->setSpeed(TURN_SPEED, TURN_ANGULAR_SPEED);
	}

	virtual ~TurnLeft();
};

#endif /* TURNLEFT_H_ */
