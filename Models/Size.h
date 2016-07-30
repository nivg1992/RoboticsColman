
#ifndef SIZE_H_
#define SIZE_H_

#include <algorithm>

class Size {
public:
	float m_Height;
	float m_Width;
	Size();
	Size(float Height, float Width);
	float RadiosSize ();
	virtual ~Size();
};

#endif /* SIZE_H_ */
