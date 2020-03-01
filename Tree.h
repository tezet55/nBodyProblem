#pragma once
#include "data.h"
#include "Body.h"
#include "Quadrant.h"
class Tree
{
public:
	int nBodies = 0;

	Quadrant* quadrant = NULL;
	Body* body = NULL;

	Tree* NW = NULL;
	Tree* NE = NULL;
	Tree* SW = NULL;
	Tree* SE = NULL;

	bool isExternal()
	{
		if (NW == NULL && NE == NULL && SW == NULL && SE == NULL)
			return true;
		else
			return false;
	}

	void addBody(Body* newBody)
	{
		Quadrant* mainQuadrant = quadrant;
		double dim = mainQuadrant->diameter / 2;
		double posX = mainQuadrant->posX;
		double posY = mainQuadrant->posY;

		Quadrant northwest;
		northwest.diameter = dim;
		northwest.posX = posX - dim / 2;
		northwest.posY = posY + dim / 2;

		Quadrant northeast;
		northeast.diameter = dim;
		northeast.posX = posX + dim / 2;
		northeast.posY = posY + dim / 2;

		Quadrant southwest;
		southwest.diameter = dim;
		southwest.posX = posX - dim / 2;
		southwest.posY = posY - dim / 2;

		Quadrant southeast;
		southeast.diameter = dim;
		southeast.posX = posX + dim / 2;
		southeast.posY = posY - dim / 2;

		if (nBodies == 1)
		{
			Body* c = body;
			if (northwest.isIn(c))
			{
				if (!NW)
				{
					NW = new Tree;
					//newTree(NW);
					NW->quadrant = new Quadrant;
					*NW->quadrant = northwest;
				}
				NW->addBody(c);
			}
			else if (northeast.isIn(c))
			{
				if (!NE)
				{
					NE = new Tree;
					//newTree(NE);
					NE->quadrant = new Quadrant;
					*NE->quadrant = northeast;
				}
				NE->addBody(c);
			}
			else if (southwest.isIn(c))
			{
				if (!SW)
				{
					SW = new Tree;
					//newTree(SW);
					SW->quadrant = new Quadrant;
					*SW->quadrant = southwest;
				}
				SW->addBody(c);
			}
			else if (southeast.isIn(c))
			{
				if (!SE)
				{
					SE = new Tree;
					//newTree(SE);
					SE->quadrant = new Quadrant;
					*SE->quadrant = southeast;
				}
				SE->addBody(c);
			}
		}

		if (nBodies >= 1)
		{
			nBodies += 1;
			if (northwest.isIn(newBody))
			{
				if (!NW)
				{
					NW = new Tree;
					//newTree(NW);
					NW->quadrant = new Quadrant;
					*NW->quadrant = northwest;
				}
				NW->addBody(newBody);
			}
			else if (northeast.isIn(newBody))
			{
				if (!NE)
				{
					NE = new Tree;
					//newTree(NE);
					NE->quadrant = new Quadrant;
					*NE->quadrant = northeast;
				}
				NE->addBody(newBody);
			}
			else if (southwest.isIn(newBody))
			{
				if (!SW)
				{
					SW = new Tree;
					//newTree(SW);
					SW->quadrant = new Quadrant;
					*SW->quadrant = southwest;
				}
				SW->addBody(newBody);
			}
			else if (southeast.isIn(newBody))
			{
				if (!SE)
				{
					SE = new Tree;
					//newTree(SE);
					SE->quadrant = new Quadrant;
					*SE->quadrant = southeast;
				}
				SE->addBody(newBody);
			}
		}
		if (nBodies == 0)
		{
			body = new Body;
			*body = *newBody;				//Czy to dzia³a?
			nBodies = 1;
		}
		else
			body->massCenter(newBody);
	}

	void delTree()
	{
		if (NW != NULL)
		{
			NW->delTree();
			delete NW->body;
			delete NW->quadrant;
			delete NW->NW;
			delete NW->NE;
			delete NW->SW;
			delete NW->SE;
			delete NW;
			NW = NULL;
		}
		if (NE != NULL)
		{
			NE->delTree();
			delete NE->body;
			delete NE->quadrant;
			delete NE->NW;
			delete NE->NE;
			delete NE->SW;
			delete NE->SE;
			delete NE;
			NE = NULL;
		}
		if (SW != NULL)
		{
			SW->delTree();
			delete SW->body;
			delete SW->quadrant;
			delete SW->NW;
			delete SW->NE;
			delete SW->SW;
			delete SW->SE;
			delete SW;
			SW = NULL;
		}
		if (SE != NULL)
		{
			SE->delTree();
			delete SE->body;
			delete SE->quadrant;
			delete SE->NW;
			delete SE->NE;
			delete SE->SW;
			delete SE->SE;
			delete SE;
			SE = NULL;
		}
	}

	void updateForce(Body* b) {

		if (body == NULL || b->isEqual(body))
			return;

		if (nBodies == 1)
			b->accelerate(*body);
		else {

			double s = quadrant->diameter;

			double disX = b->posX - body->posX;
			double disY = b->posY - body->posY;
			double dis = sqrt(disX * disX + disY * disY);

			if ((s / dis) < 2)
				b->accelerate(*body);

			else {
				if (NW != NULL)
					NW->updateForce(b);
				if (NE != NULL)
					NE->updateForce(b);
				if (SW != NULL)
					SW->updateForce(b);
				if (SE != NULL)
					SE->updateForce(b);
			}
		}
	}
};