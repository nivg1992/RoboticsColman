#include "Location.h"

using namespace std;

Location::Location(double x, double y, double Yaw)
{
	m_X = x;
	m_Y = y;
	m_Yaw = Yaw;
}

Location::Location()
{
	m_X = 0;
	m_Y = 0;
	m_Yaw = 0;
}


Location::~Location() {
	// TODO Auto-generated destructor stub
}

