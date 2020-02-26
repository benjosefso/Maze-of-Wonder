/*
	CPP File for Room Class

	See Source.cpp for full description.

	Jake Gibson and Ben Josefson

	5/7/19
*/


#include "Room.h"
#define STB_IMAGE_IMPLEMENTATION


Room::Room() 
{
	
}

Room::Room(vec3 loca, GLint tpe, GLint en, bool lst)
{
	loc = loca;
	type = tpe;
	entry = en;
	last = lst;

	walls[0] = false;
	walls[1] = false;
	walls[2] = false;
	walls[3] = false;

	switch (type)
	{
	case 0:
		break;
	case 1:
			walls[0] = true;
			break;
	case 2:
			walls[3] = true;
			break;
	case 3:
			walls[1] = true;
			break;
	case 4:
			walls[2] = true;
			break;
		case 5:
			walls[1] = true;
			walls[3] = true;
			break;
		case 6:
			walls[0] = true;
			walls[2] = true;
			break;
		case 7:
			walls[0] = true;
			walls[1] = true;
			break;
		case 8:
			walls[0] = true;
			walls[3] = true;
			break;
		case 9:
			walls[2] = true;
			walls[3] = true;
			break;
		case 10:
			walls[1] = true;
			walls[2] = true;
			break;
	case 11:
			walls[1] = true;
			walls[2] = true;
			walls[3] = true;
			break;
		case 12:
			walls[0] = true;
			walls[1] = true;
			walls[2] = true;
			break;
		case 13:
			walls[0] = true;
			walls[1] = true;
			walls[3] = true;
			break;
		case 14:
			walls[0] = true;
			walls[2] = true;
			walls[3] = true;
			break;
	}


}

void Room::drawRoom() 
{

	GLfloat mat_ambient[] = { 0.0 , 0.0 , 0.0 , 1.0 };
	GLfloat mat_diffuse[] = { 0.01 , 0.01 , 0.01 , 1.0 };
	GLfloat mat_specular[] = { 0.5 , 0.5 , 0.5, 1.0 };
	GLfloat mat_shininess[] = { 32 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	// bottom wall ("floor")
	glBegin(GL_QUADS);
		glVertex3f(loc.x-ROOMSIZE, loc.y-0.01, loc.z-ROOMSIZE);
		glVertex3f(loc.x-ROOMSIZE, loc.y -0.01, loc.z+ROOMSIZE);
		glVertex3f(loc.x+ROOMSIZE, loc.y -0.01, loc.z+ROOMSIZE);
		glVertex3f(loc.x+ROOMSIZE, loc.y -0.01, loc.z-ROOMSIZE);
	glEnd();

	/*
	// top wall ("roof")
	glBegin(GL_QUADS);
		glVertex3f(loc.x - ROOMSIZE, loc.y + HEIGHT, loc.z - ROOMSIZE);
		glVertex3f(loc.x - ROOMSIZE, loc.y + HEIGHT, loc.z + ROOMSIZE);
		glVertex3f(loc.x + ROOMSIZE, loc.y + HEIGHT, loc.z + ROOMSIZE);
		glVertex3f(loc.x + ROOMSIZE, loc.y + HEIGHT, loc.z - ROOMSIZE);
	glEnd();
	*/

	//wallTex();
	mat_ambient[0] = 0.24725; mat_ambient[1] = 0.1995; mat_ambient[2] = 0.0745;
	mat_diffuse[0] = 0.75164; mat_diffuse[1] = 0.60648; mat_diffuse[2] = 0.22648;
	mat_specular[0] = 0.628281; mat_specular[1] = 0.555802; mat_specular[2] = 0.366065;
	mat_shininess[0] = 51.2;
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	// north wall
	if (walls[0])
	{
		
		glBegin(GL_QUADS);
		glColor3f(0.5, 0, 0);
			glVertex3f(loc.x - ROOMSIZE, loc.y - 0.01, loc.z + ROOMSIZE);
			glVertex3f(loc.x + ROOMSIZE, loc.y - 0.01, loc.z + ROOMSIZE);
			glVertex3f(loc.x + ROOMSIZE, loc.y + HEIGHT, loc.z + ROOMSIZE);
			glVertex3f(loc.x - ROOMSIZE, loc.y + HEIGHT, loc.z + ROOMSIZE);
		glEnd();
	}
	// east wall
	if (walls[1])
	{
		glBegin(GL_QUADS);
		glColor3f(0.5, 0, 0);
			glVertex3f(loc.x + ROOMSIZE, loc.y - 0.01, loc.z - ROOMSIZE);
			glVertex3f(loc.x + ROOMSIZE, loc.y - 0.01, loc.z + ROOMSIZE);
			glVertex3f(loc.x + ROOMSIZE, loc.y + HEIGHT, loc.z + ROOMSIZE);
			glVertex3f(loc.x + ROOMSIZE, loc.y + HEIGHT, loc.z - ROOMSIZE);
		glEnd();
	}
	// south wall
	if (walls[2])
	{
		glBegin(GL_QUADS);
		glColor3f(0.5, 0, 0);
			glVertex3f(loc.x - ROOMSIZE, loc.y - 0.01, loc.z - ROOMSIZE);
			glVertex3f(loc.x + ROOMSIZE, loc.y - 0.01, loc.z - ROOMSIZE);
			glVertex3f(loc.x + ROOMSIZE, loc.y + HEIGHT, loc.z - ROOMSIZE);
			glVertex3f(loc.x - ROOMSIZE, loc.y + HEIGHT, loc.z - ROOMSIZE);
		glEnd();
	}
	// west wall
	if (walls[3])
	{
		glBegin(GL_QUADS);
		glColor3f(0.5, 0, 0);
			glVertex3f(loc.x - ROOMSIZE, loc.y - 0.01, loc.z - ROOMSIZE);
			glVertex3f(loc.x - ROOMSIZE, loc.y - 0.01, loc.z + ROOMSIZE);
			glVertex3f(loc.x - ROOMSIZE, loc.y + HEIGHT, loc.z + ROOMSIZE);
			glVertex3f(loc.x - ROOMSIZE, loc.y + HEIGHT, loc.z - ROOMSIZE);
		glEnd();
	}
	glColor3f(1, 1, 1);
}


bool* Room::getWalls() { return walls; }

bool Room::isLast() { return last; }

GLint Room::getEntry() { return entry; }

GLint Room::getExit() { return gexit; }

GLint Room::getExit2() { 
	switch (gexit) {
	case 0: return 2;
		break;
	case 1: return 3;
		break;
	case 2: return 0;
		break;
	case 3: return 1;
		break;
	}
}

void Room::setExit(int e) { gexit = e; }

vec3 Room::getLoc() { return loc; }

GLint Room::getType() { return type; }

