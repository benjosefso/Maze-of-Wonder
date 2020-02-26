/*

											CAN YOU NAVIGATE THE MAZE OF MYSTERY AND FIND THE GOLDEN TEAPOT?

														Use WASD to move and mouse to look around.
																	  Q to quit.

															Jake Gibson and Ben Josefson

																	    5/7/19



Driver File for Maze Game
Code taken from labs on p-drive
Camera class borrowed and cited in camera.h

The maze of mystery is not a fully functioning game and thus collision with walls is not handled.

*/
#include <GL/glew.h>

#include <GL/GL.h>

#include <GL/glut.h>

#include <Angel.h>
#include "Camera.h"
#include "Room.h"
#include "Maze1.h"
#include <time.h>



#define WINDOW 500;

GLint wid = WINDOW;
GLint hig = WINDOW;

// light position
GLfloat xl = 1.5, yl = 1.5, zl = 1.5;

// initial camera position
GLfloat eyex = 0, eyey = 0, eyez = 0;

// view rotation 
GLfloat pitch = 0;
GLfloat yaw = 0;
GLint lastx = 0, lasty = 0;

// material properties
GLfloat mat_ambient[] = { 1.0 , 1.0 , 1.0 , 1.0 };
GLfloat mat_diffuse[] = { 0.01 , 0.01 , 0.01 , 1.0 };
GLfloat mat_specular[] = { 0.01 , 0.01 , 0.01 , 1.0 };
GLfloat mat_emission[] = { 1.0 , 1.0 , 0.0 , 0.0 };
GLfloat mat_shininess[] = { 32 };

Camera cam;

static GLint fogMode;

int currentRoom;

void myInit()
{
	// clear color, it will be the "background"
	glClearColor(0.3, 0.3, 0.8, 1.0);

	glutSetCursor(GLUT_CURSOR_NONE);
	// enable depth test
	glEnable(GL_DEPTH_TEST);

	// enable lighting and the first light source
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// let OpenGL normalize the normal vectors
	glEnable(GL_NORMALIZE);

	// interpolate the colors on the surface of the polygon "smoothly"
	glShadeModel(GL_SMOOTH);

	// define properties of the light source, at a point
	GLfloat light_position[] = { 40,50,-40,1 };
	GLfloat light_diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light_ambient[] = { 0.8,0.8,0.8,1.0 };
	GLfloat light_specular[] = { 1.0,1.0,1.0,1.0 };

	// assign the above properties to light source 0
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glColor3f(1, 1, 1);
	cam = Camera();
	glFrustum(-1, 1, -1, 1, 1, 80);
	
	glEnable(GL_FOG);

	{
		GLfloat fogColor[4] = { 0.6 , 0.5 , 0.6 , 1.0 };

		fogMode = GL_EXP;
		glFogi(GL_FOG_MODE, fogMode);
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogf(GL_FOG_DENSITY, 0.20);
		glHint(GL_FOG_HINT, GL_DONT_CARE);
		glFogf(GL_FOG_START, 1.0);
		glFogf(GL_FOG_END, 5.0);
	}

	// Fog Color
	glClearColor(0.6, 0.5, 0.6, 1.0);
	
	// generates maze
	// fills maze with empty rooms
	// random generation of rooms
	/*srand(time(0));
	bool isEnd = false;
	int length = 0;
	int type = -1;
	lastRm.setExit(0);
	int roomnum = 0;
	int mazeCenterx = MAZESIZE / 2;
	int mazeCentery = MAZESIZE / 2;
	int mazex;
	int mazey;
	for (int i = 0; i < MAZESIZE*MAZESIZE; i++) {
		if (length == MAZESIZE) {
			isEnd = true;
			if (lastRm.getExit() == 0) {
				type = 13;
			}
			else if (lastRm.getExit() == 1) {
				type = 12;
			}
			else if (lastRm.getExit() == 2) {
				type = 11;
			}
			else if (lastRm.getExit() == 3) {
				type = 14;
			}
			goto Done;
		}
		else {
			if (type == -1) {
				type = 5;
				mazex = mazeCenterx;
				mazey = mazeCentery;
				maze[mazex][mazey] = type;
				roomnum++;
			}
			else if (lastRm.getExit() == 0) {
				do {
					type = rand() % 11;
				} while (type == 4 || type == 6 || type == 9 || type == 10);
				mazey++;
				maze[mazex][mazey] = type;
				roomnum++;
			}
			else if (lastRm.getExit() == 1) {
				do {
					type = rand() % 11;
				} while (type == 2 || type == 5 || type == 8 || type == 9);
				mazex++;
				maze[mazex][mazey] = type;
				roomnum++;
			}
			else if (lastRm.getExit() == 2) {
				do {
					type = rand() % 11;
				} while (type == 1 || type == 6 || type == 7 || type == 8);
				mazey--;
				maze[mazex][mazey] = type;
				roomnum++;
			}
			else if (lastRm.getExit() == 3) {
				do {
					type = rand() % 11;
				} while (type == 3 || type == 5 || type == 7 || type == 10);
				mazex--;
				maze[mazex][mazey] = type;
				roomnum++;
			}
		}

		rooms[i] = Room(lastRm.getLoc() + dir[lastRm.getExit()], types[type], lastRm.getExit2(), isEnd);
		if ((type >= 0 && type < 5)) {
			bool *walls;
			walls = rooms[i].getWalls();
			int entry = rooms[i].getEntry();
			int gexit;
			if (maze[mazex - 1][mazey] != -1) walls[3] = true;
			if (maze[mazex + 1][mazey] != -1) walls[1] = true;
			if (maze[mazex][mazey - 1] != -1) walls[2] = true;
			if (maze[mazex][mazey + 1] != -1) walls[0] = true;
			do {
				gexit = rand() % 4;
			} while (walls[gexit] || gexit == entry);
			rooms[i].setExit(gexit);
		}
		lastRm = rooms[i];
		length++;

	}
Done:
	length = 0;
	for (int i = 0; i < MAZESIZE; i++){
		for (int j = 0; j < MAZESIZE; j++) {
			std::cout << maze[i][j] << '\t';
		}
		std::cout << std::endl;
	}
	 
*/
	for (int i = 0; i < MAZESIZE; i++) {
		for (int j = 0; j < MAZESIZE; j++) {
			locs[i][j] = vec3(j * 8, 0, i * -8);
		}
	}
	bool isEnd = false;
	for (int i = 0; i < MAZESIZE; i++) {
		for (int j = 0; j < MAZESIZE; j++) {
			rooms[i][j] = Room(locs[i][j], maze[i][j], 0, isEnd);
		}
	}
}
void display(void)
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	cam.GetViewMatrix();


	for (int i = 0; i < MAZESIZE; i++) {
		for (int j = 0; j < MAZESIZE; j++) {
			rooms[i][j].drawRoom();
		}
	}

	glPushMatrix();

	glTranslatef(72, 2.0, -72);
	glutSolidTeapot(1);
	glPopMatrix();
	glutSwapBuffers();
}

void mouse(int x, int y)
{
	
	GLfloat deltax = x - lastx;
	GLfloat deltay = y - lasty;

	lastx = wid/2;
	lasty = hig/2;

	/*
	deltax *= 0.25;
	deltay *= 0.25;

	yaw += deltax;
	pitch += deltay;

	if (pitch > 89.0)
		pitch = 89.0;
	if (pitch < -89.0)
		pitch = -89.0;
		*/
	cam.ProcessMouseMovement(deltax, deltay);

	glutWarpPointer(wid/2, hig/2);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{

	/* keyboard callback, selects an axis about which to rotate */
	switch (key) {
	case 'w':
	case 'W':
		cam.ProcessKeyboard(FORWARD, 0.1);
		break;
	case 's':
	case 'S':
		cam.ProcessKeyboard(BACKWARD, 0.1);
		break;
	case 'd':
	case 'D':
		cam.ProcessKeyboard(RIGHT, 0.1);
		break;
	case 'a':
	case 'A':
		cam.ProcessKeyboard(LEFT, 0.1);
		break;
	case 'q':
	case 'Q':
		exit(0);
	}
	glutPostRedisplay();
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	wid = w;
	hig = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (double)w / h, 1, 20);
	glMatrixMode(GL_MODELVIEW);
}

void getCurrentRoom(int x, int z) 
{
	int currx = 2;
	int curry = 3;
}

void
main(int argc, char **argv)
{
	glutInit(&argc, argv);

	/* need both double buffering and z buffer */

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(5000, 5000);
	glutCreateWindow("Maze of Mystery");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(mouse);
	glEnable(GL_DEPTH_TEST); /* Enable hidden--surface--removal */

	myInit();

	glutMainLoop();
}