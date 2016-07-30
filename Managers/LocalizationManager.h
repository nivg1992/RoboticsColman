#pragma once

#include <vector>
#include "../Particle.h"
#include "../Models/Location.h"
#include "../Consts.h"
#include <float.h>

using namespace std;

namespace Managers {

class LocalizationManager {

public:
	// Data Member
	Location currLocation;
	AnotherMap* m_Map;

	// Function
	void update(float deltaX, float deltaY, float deltaYaw, float laserArr[], Cell* nextWaypoint);
	Location BestLocation();

	// Ctor
	LocalizationManager(Location currLocation, AnotherMap* currMap,
			double maxDistance, LaserProxy* laserProxy);

	// Dtor
	~LocalizationManager();

protected:
	// Data Member
	vector<Particle*> particles;
};
}
