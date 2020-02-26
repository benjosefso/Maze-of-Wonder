/*
	Header File for Maze Class

	See Source.cpp for full description.

	Jake Gibson and Ben Josefson

	5/7/19
*/

#include "Room.h"
#define MAZESIZE 10



vec3 north = vec3(0, 0, ROOMSIZE*2);
vec3 east = vec3(ROOMSIZE*2, 0, 0);
vec3 west = vec3(-ROOMSIZE*2, 0, 0);
vec3 south = vec3(0, 0, -ROOMSIZE*2);

vec3 dir[4] = { north, east, south, west };

char types[15][2] = { 
	{'0', 'A'},																// type 0 - no walls
	{'1', 'A'}, {'1', 'B'}, {'1', 'C'}, {'1','D'},							// type 1-north || type 2-west || type3-east || type4-south
	{'2', 'A'}, {'2', 'B'}, {'2', 'C'}, {'2', 'D'}, {'2', 'E'}, {'2', 'F'},	// type6-N/S hallway || type7-E/W hallway || type8-NE || type9-NW || type10-SW || type11-SE
	{'3', 'A'}, {'3', 'B'}, {'3', 'C'}, {'3', 'D'}};						// type 1-open north || type 2-open west || type3-open south || type4-open east

Room lastRm = Room(vec3(0, 0, 0), 0, 2, false);

Room empty = Room(vec3(-ROOMSIZE, -ROOMSIZE, 0), 0, 0, false);

Room rooms[MAZESIZE][MAZESIZE];

GLint maze[MAZESIZE][MAZESIZE]={ {14,1,6,7,8,7,14,6,1,7}, {8,10,13,5,5,2,6,6,10,5}, {9,7,5,5,5,11,8,6,6,7},{8,10,5,5,9,7,9,7,15,5},
{5,14,4,4,1,10,8,10,5,5},{5,8,6,7,5,8,4,12,2,3},{2,4,12,5,11,5,13,8,3,13},{5,8,7,2,7,5,5,9,6,3},{9,10,5,5,5,5,9,6,6,3},{14,6,10,11,9,4,6,6,12,11} };

vec3 locs[MAZESIZE][MAZESIZE];
