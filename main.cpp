#include "data.h"
#include "ród³o1.h"

Body body[N];
Tree *mainNode = new Tree;

int main(int argc, char** argv)
{
	mainNode->quadrant = new Quadrant;
	mainNode->quadrant->posX = sizeX / 2 + 1500;
	mainNode->quadrant->posY = sizeY / 2 + 1000;
	mainNode->quadrant->diameter = 100 * sizeX;
	const int window_size = 700;
	srand(time(NULL));
	for (int i = 0; i < N; i++)
	{
		body[i].generate();
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(window_size+200, window_size);
	glutInitWindowPosition(50, 50);
	auto win = glutCreateWindow("nBodyProblem");

	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window_size+200, window_size, 0, 0, 1);


	glutDisplayFunc(display);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();

	tick(0);

	glutMainLoop();


}

void tick(int i)
{
	update_particles();
	glutTimerFunc(1, tick, 0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);


	for (int i = 0; i < N; i++)
	{
		float pos_x = body[i].posX / 75;
		float pos_y = body[i].posY / 75;
		float radius = 0.5;


		glColor3f((rand() % 100) / 100, 1, 1);
		glBegin(GL_POLYGON);
		for (float a = 0; a < 2 * 3.14159265359; a += 0.1) {
			glVertex2f(radius * cos(a) + pos_x, radius * sin(a) + pos_y);
		}
		glEnd();
	}

	glFlush();

}
void update_particles()
{
	for (int i = 0; i < N; i++)
	{
		body[i].force[0] = 0;
		body[i].force[1] = 0;
		mainNode->addBody(&body[i]);
	}
	
	for (int i = 0; i < N; i++)
	{
		mainNode->updateForce(&body[i]);
		body[i].move();
	}

	mainNode->delTree();
	mainNode->nBodies = 0;
	mainNode->NE = NULL;
	mainNode->NW = NULL;
	mainNode->SE = NULL;
	mainNode->SW = NULL;
	mainNode->body = NULL;
	display();
}
