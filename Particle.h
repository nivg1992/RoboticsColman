#pragma once

#include "Consts.h"
#include "Utils/MathUtil.h"
#include "Models/AnotherMap.h"
#include <libplayerc++/playerc++.h>
#include <math.h>
#include <float.h>
#include "Managers/ConfigurationManager.h"
#include "Models/Cell.h"

using namespace std;
using namespace PlayerCc;
using namespace Consts;
using namespace Managers;

class Particle {

private:
	AnotherMap* map;

public:
	float x;
	float y;
	float yaw;
	float belief;
	double maxDistance;
	LaserProxy* laserProxy;

	Particle();
	void SetLaserProxy(LaserProxy* lp) {
		this->laserProxy = lp;
	}
	Particle(float x, float y, float yaw, float belief);
	~Particle();
	void SetMap(AnotherMap* map);
	void SetMaxDistance(double maxDistance);

	void Update(float deltaX, float deltaY, float deltaYaw, float laserArray[], Cell* nextWaypoint);
	float ProbMovement(float deltaX, float deltaY, float deltaYaw);
	float ProbByScan(float laserArray[]);
	float Randomize(float min, float max);

	Particle* CreateChild(float expansionRadius, float yawRange);
};

