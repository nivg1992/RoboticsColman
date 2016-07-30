#include "Size.h"

using namespace std;

float Size::RadiosSize ()
{
	return std::max(m_Height,m_Width);
}

Size::Size(float Height, float Width)
{
	m_Height = Height;
	m_Width = Width;
}

Size::Size()
{
	m_Height = 0;
	m_Width = 0;
}


Size::~Size() {
}

