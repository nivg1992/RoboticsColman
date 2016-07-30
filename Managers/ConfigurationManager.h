#pragma once

#include <string>
#include <iostream>

using namespace std;
#include "../Models/Location.h"
#include "../Models/Size.h"

namespace Managers {
	class ConfigurationManager {
	public:
		virtual ~ConfigurationManager();
		static ConfigurationManager* GetInstance();
		static ConfigurationManager* LoadFromFile(string filePath);
		string getPngMapPath();
		Location getStartLocation();
		Location getEndLocation();
		float getPixelPerCm();
		float getPngGridResolution();
		Size getRobotSize();

	private:
		ConfigurationManager();
		static ConfigurationManager * m_ConfigurationManagerInstance;
		string m_PngMapPath;
		Location m_StartLocation;
		Location m_EndLocation;
		float m_PpCM;
		float m_PngGridResolution;
		Size m_RobotSize;
	};

	//ConfigurationManager * ConfigurationManager::m_ConfigurationManagerInstance = NULL;
}
