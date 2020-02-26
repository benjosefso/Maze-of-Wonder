/*
	Header File for Room Class

	See Source.cpp for full description.

	Jake Gibson and Ben Josefson

	5/7/19
*/

#pragma once

#include <Angel.h>
#include <GL/glut.h>

#define ROOMSIZE 4
#define HEIGHT 4

class Room 
{
private:
	GLint entry;
	GLint gexit;
	bool walls[4];
	vec3 loc;
	GLint type;
	bool last;
public:
	Room();
	Room(vec3, GLint, GLint, bool);

	void drawRoom();

	bool* getWalls();
	bool isLast();

	GLint getEntry();
	GLint getExit();
	GLint getExit2();
	GLint getType();
	void setExit(int);

	void wallTex();

	vec3 getLoc();
};