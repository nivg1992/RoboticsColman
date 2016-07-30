#pragma once

#include "../Models/Waypoint.h"
#include "../Models/Cell.h"
#include "../Robot.h"
#include "../Consts.h"
#include "../Utils/MathUtil.h"

using namespace std;
using namespace Consts;
using namespace Utils;

namespace Managers {

	class WaypointsManager {
		public:
			WaypointsManager(vector<Cell*> waypoints);
			virtual ~WaypointsManager();

			bool WaypointDriver(Cell* wp, Robot rob);
			bool IsInWaypoint(double xp, double yp);
			vector<Cell*> smoothWaypoints;
			Cell* currWaypoint;
			double longestDistance;

		protected:
			void SmoothWaypoints();

		private:
			vector<Cell*> waypointsVec;

};
}
