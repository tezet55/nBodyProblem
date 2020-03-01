#pragma once
#include "data.h"
#include "Body.h"

class Quadrant
{
public:
	double posX;
	double posY;
	double diameter;

	bool isIn(Body* b)
	{
		if (b->posX >= (posX - diameter / 2) && b->posX <= (posX + diameter / 2) && b->posY >= (posY - diameter / 2) && b->posY <= (posY + diameter / 2))
			return true;
		return false;
	}
};