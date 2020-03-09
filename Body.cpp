#pragma once
#include "data.h"

class Body
{
public:
    unsigned long long int mass;
    double posX;
    double posY;
    double force[2];
    double velocity[2];

	void generate()
	{
		mass = pow(10, (int)(rand() % 10));
		posX = rand() % sizeX + 15000;
		posY = rand() % sizeY + 10000;
		force[0] = 0;
		force[1] = 0;
		velocity[0] = 0;
		velocity[1] = 0;
	}

	void accelerate(Body nextBody)
	{
		double disX = nextBody.posX - posX;
		double disY = nextBody.posY - posY;
		double dis = sqrt(disX * disX + disY * disY);
		double calForce = (G * mass * nextBody.mass) / (sqrt(dis));
		force[0] += calForce * disX / dis;
		force[1] += calForce * disY / dis;
	}

	void massCenter(Body* b)
	{
		unsigned long long m = mass + b->mass;
		posX = (posX * mass + b->posX * b->mass) / m;
		posY = (posY * mass + b->posY * b->mass) / m;
		mass = m;
	}

	void move()
	{
		velocity[0] += force[0] / mass * dt;
		velocity[1] += force[1] / mass * dt;
		posX += velocity[0] * dt;
		posY += velocity[1] * dt;
	}

	bool isEqual(Body *b)
	{
		if (posX == b->posX && posY == b->posY && mass == b->mass)
			return true;
		return false;
	}

};