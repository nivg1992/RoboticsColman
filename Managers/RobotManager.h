#pragma once

#include <vector>
#include <libplayerc++/playerc++.h>

#include "../Consts.h"
#include "../behaviors/Behavior.h"
#include "../Robot.h"
#include "LocalizationManager.h"
#include "WaypointsManager.h"
#include "../behaviors/MoveForward.h"
//#include "../behaviors/TurnInPlace.h"
#include "../behaviors/TurnLeft.h"
#include "../behaviors/TurnRight.h"


using namespace PlayerCc;
using namespace std;
using namespace Consts;

namespace Managers {

	class RobotManager {

		public:
			RobotManager(PlayerClient* player);
			RobotManager(const string hostname = PLAYER_HOST, uint port = PLAYER_PORT);

			virtual ~RobotManager();

			void setLocalizationManager(LocalizationManager* localizationManager);
			void setWaypoints(vector<Cell*> landmarks);
			void run();

		private:
			Behavior* m_CurrBehavior;
			vector<Behavior*> m_Behaviors;
			LocalizationManager* m_LocalizationManager;
			WaypointsManager* m_WaypointsManager;
			Robot* m_Robot;
			Location m_RealLocation;

			void initBehaviors();
			void updateLocation();
			void runStep();
	};
}
