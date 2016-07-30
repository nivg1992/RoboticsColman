#pragma once

#include "ConfigurationManager.h"
#include <iostream>
#include <string>
#include "../lib/config.h"
#include "../Consts.h"
using namespace std;
using namespace Consts;

namespace Managers {
ConfigurationManager *ConfigurationManager::m_ConfigurationManagerInstance = NULL;

ConfigurationManager::ConfigurationManager(){};

ConfigurationManager* ConfigurationManager::LoadFromFile(string filePath) {
		// create the first singleton instance

		Config configParser(filePath);

		ConfigurationManager::m_ConfigurationManagerInstance = new ConfigurationManager();
		ConfigurationManager::m_ConfigurationManagerInstance->m_PngMapPath = configParser.mapLocation;
		ConfigurationManager::m_ConfigurationManagerInstance->m_StartLocation.m_X = configParser.startLocation[0];
		ConfigurationManager::m_ConfigurationManagerInstance->m_StartLocation.m_Y = configParser.startLocation[1];
		ConfigurationManager::m_ConfigurationManagerInstance->m_StartLocation.m_Yaw = configParser.startLocation[2];
		ConfigurationManager::m_ConfigurationManagerInstance->m_EndLocation.m_X = configParser.goal[0];
		ConfigurationManager::m_ConfigurationManagerInstance->m_EndLocation.m_Y = configParser.goal[1];
		ConfigurationManager::m_ConfigurationManagerInstance->m_PpCM = configParser.mapResolutionCm;
		ConfigurationManager::m_ConfigurationManagerInstance->m_PngGridResolution = configParser.gridResolutionCm;
		ConfigurationManager::m_ConfigurationManagerInstance->m_RobotSize.m_Width = configParser.robotSize[0];
		ConfigurationManager::m_ConfigurationManagerInstance->m_RobotSize.m_Height = configParser.robotSize[1];
		return ConfigurationManager::m_ConfigurationManagerInstance;
	}

ConfigurationManager::~ConfigurationManager() {
	}


ConfigurationManager* ConfigurationManager::GetInstance() {
	if (ConfigurationManager::m_ConfigurationManagerInstance == NULL)
	{
		throw new std::string("Object ConfigurationManager Never Loaded");
	}
	else
	{
		return ConfigurationManager::m_ConfigurationManagerInstance;
	}
	return NULL;
	}


	string ConfigurationManager::getPngMapPath() {
		return m_PngMapPath;
	}

	Location ConfigurationManager::getStartLocation() {
		return m_StartLocation;
	}

	Location ConfigurationManager::getEndLocation() {
		return m_EndLocation;
	}

	float ConfigurationManager::getPixelPerCm() {
		return m_PpCM;
	}

	float ConfigurationManager::getPngGridResolution() {
		return m_PngGridResolution;
	}

	Size ConfigurationManager::getRobotSize() {
		return m_RobotSize;
	}

}
