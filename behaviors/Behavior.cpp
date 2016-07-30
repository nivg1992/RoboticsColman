/*
 * Behavior.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#include "Behavior.h"

Behavior::Behavior(Robot* robot) {
	_robot = robot;

}

Behavior::~Behavior() {
	delete _robot;
	_robot = NULL;
}
