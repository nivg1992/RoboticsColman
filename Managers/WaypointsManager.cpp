#include "WaypointsManager.h"

#define WAYPOINT_SKIPS 3
#define INCLINE_INACCURACY DBL_EPSILON
#define FORCE_WAYPOINT_ON 2

namespace Managers {

WaypointsManager::WaypointsManager(vector<Cell*> waypoints) {
	this->waypointsVec = waypoints;
	SmoothWaypoints();
	currWaypoint = NULL;
}

void WaypointsManager::SmoothWaypoints() {
	unsigned currentY = waypointsVec[0]->getY();
	unsigned currentX = waypointsVec[0]->getX();
	float firstIncline = MathUtil::incline(waypointsVec[0]->getX(),
			waypointsVec[0]->getY(), waypointsVec[1]->getX(),
			waypointsVec[1]->getY());
	longestDistance = MathUtil::distance(currentX, currentY, waypointsVec[0]->getX(), waypointsVec[0]->getY());
	int lastPut = 0;
	//smoothWaypoints.push_back(waypointsVec[0]);

	for (unsigned i = 1; i < waypointsVec.size() - 1; i += WAYPOINT_SKIPS) {
		lastPut++;
		unsigned y = waypointsVec[i+1]->getY();
		unsigned x = waypointsVec[i+1]->getX();
		float currIncline = MathUtil::incline(currentX, currentY, x, y);

		if((currIncline != firstIncline && abs(currIncline - firstIncline) >= INCLINE_INACCURACY) || lastPut > FORCE_WAYPOINT_ON)
		{
			lastPut = 0;
			longestDistance = std::max(
					longestDistance,
					MathUtil::distance((double)currentX, (double)currentY, (double)waypointsVec[i]->getX(), (double)waypointsVec[i]->getY())
			);
			currentY = y;
			currentX = x;
			smoothWaypoints.push_back(waypointsVec[i]);
			firstIncline = currIncline;
		}
	}

	Cell* lastSmooth = smoothWaypoints[smoothWaypoints.size() - 1];
	Cell* lastWaypoint = waypointsVec[waypointsVec.size() - 1];
	if (lastSmooth != lastWaypoint) {
		smoothWaypoints.push_back(lastWaypoint);
	}
	this->currWaypoint = smoothWaypoints[0];
}

WaypointsManager::~WaypointsManager() {
	delete currWaypoint;
	currWaypoint = NULL;
}

bool WaypointsManager::WaypointDriver(Cell* wp, Robot rob) {
	return false;

}

bool WaypointsManager::IsInWaypoint(double xp, double yp) {
	return MathUtil::inRange(xp, currWaypoint->getX() - 2, currWaypoint->getX() + 2)
			&& MathUtil::inRange(yp, currWaypoint->getY() - 2, currWaypoint->getY() + 2);

}
}
