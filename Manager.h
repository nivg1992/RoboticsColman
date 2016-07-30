/*
 * Manager.h
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#ifndef MANAGER_H_
#define MANAGER_H_
#include "Plans/PlnObstacleAvoid.h"
#include "Robot.h"
#include "Managers/WaypointsManager.h"
#include "Managers/LocalizationManager.h"
#include "Models/AnotherMap.h"
#include "Models/Cell.h"
#include <unistd.h>

using namespace Managers;

class Manager {
	Behavior* currentPoint;
	Robot* robot;
	Plan* plan;

public:
	Manager(Robot* robot, Plan* pln);
	void run();
	virtual ~Manager();
	void InitApp();
	WaypointsManager* waypointsManager;
	LocalizationManager* localizationManager;
	AnotherMap* map;
	Cell* start;
	Cell* destination;
	Location getBestLocation(Cell* waypoint);
	void rotateLikeShawarma(Cell* waypoint, Location* location);
};

#endif /* MANAGER_H_ */
