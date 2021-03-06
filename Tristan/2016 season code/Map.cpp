#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <random>
#include <time.h> 
#include <assert.h>
#include <unistd.h>
#include "maze.h"

using namespace std;

void loadmap(mapstruct & a){
	a.width = MAPWIDTH;
	a.length = MAPLENGTH;

	for(int i=0; i < a.width; i++)
		for(int j=0; j < a.length; j++)
			a.walls[i][j] = false;
	 
	 // blocks off secret passage
	for(int i=265; i < a.width; i++)
		for(int j=0; j < 288; j++)
			a.walls[i][j] = true;

	// blocks of outerworks
	for(int i=0; i < 267; i++)
		for(int j=191; j < 241; j++)
			a.walls[i][j] = true;

	// blocks of tower 
	for(int i=87; i < 232; i++)
		for(int j=0; j < 69; j++)
			a.walls[i][j] = true;
	
}

int main() {

	mapstruct a;
	
	loadmap(a);
}
