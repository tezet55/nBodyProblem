#pragma once

#include <stdio.h>
#include <time.h> 
#include <stdlib.h> 
#include <math.h>
#include <Windows.h>
#include <GL/freeglut.h>

#define N 20000
#define G 6.67E-11
#define sizeX 50000
#define sizeY 50000
#define dt 4



/*
struct Body
{
    unsigned long long int mass;
    double posX;
    double posY;
    double force[2];
    double velocity[2];
};

struct Quadrant
{
	double posX;
	double posY;
	double diameter;
};

struct Tree
{
	int nBodies = 0;

	Quadrant* quadrant = NULL;
	Body* body = NULL;

	Tree* NW = NULL;
	Tree* NE = NULL;
	Tree* SW = NULL;
	Tree* SE = NULL;
};
*/

void display();
void tick(int i);
void update_particles();
/*
Body accelerate(Body body, Body nextBody);
Body move(Body mvBody);
void cudaInit(Tree* t, Body* body);
void addBody(Tree *t, Body *newBody);
void delTree(Tree *t);
bool isIn(Quadrant q, Body b);
bool isExternal(Tree q);
void massCenter(Body* a, Body* b);
void updateForce(Tree t, Body* b);
*/