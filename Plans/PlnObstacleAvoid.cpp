/*
 * PlnObstacleAvoid.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "PlnObstacleAvoid.h"

PlnObstacleAvoid::PlnObstacleAvoid(Robot* robot) :
		Plan(robot) {

	//Creating Behaviors
	_beh[0] = new MoveForward(robot);
	_beh[1] = new TurnLeft(robot);
	_beh[2] = new TurnRight(robot);

	// Connecting behaviors
	for (int i = 0; i < BEHAVIOR_NUM; i++)
		for (int j = 0; j < BEHAVIOR_NUM; j++)
			if (j != i)
				this->_beh[i]->addBeh(this->_beh[j]);

	// TODO: CHECK HOW NEED BE THE FIRST?
	_start = _beh[0];
}

PlnObstacleAvoid::~PlnObstacleAvoid() {

	for (int i = 0; i < BEHAVIOR_NUM; i++)
		delete _beh[i];
}
