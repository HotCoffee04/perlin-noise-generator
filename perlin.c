#include "perlin.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Vec **grid; 
int nodesxn; //grid width in nodes
int nodesyn; //grid height in nodes
float gridWidth; //grid width in pixels
float gridHeight; //grid height in pixels

float dot(Vec v1,Vec v2); //Dot product of two vectors
float randomNum(float max); //generates random float from 0 to max
float interpolate(float t, float a, float b);
void normalizeVec( Vec* p ,int max); 


void generatePerlinVectors(int cellsxn,int cellsyn,float gWidth,float gHeight){
		
	if(grid != 0)
		clearPerlinVectors();

	nodesxn = ++cellsxn;
	nodesyn = ++cellsyn;
	
	gridWidth = gWidth;
	gridHeight = gHeight;
	
	//allocates memory for the grid
	grid = malloc(sizeof(Vec*)*nodesxn ); 
	
	for(int i = 0; i < nodesxn; i++)
		grid[i] = malloc(sizeof(Vec) * nodesyn);
	
	//generates random vectors
	for(int x = 0; x < nodesxn; x++)
		for(int y = 0; y < nodesyn; y++){
			grid[x][y].x = randomNum(2) - 1.0f;

			/*
				Vectors need to be of lenght 1.
				That's why I first generate the X coordinate and
				calculate the Y in a way that the vector length will always be 1
				(using the Pythagorean Theorem)

				However in this way all the vectors Y axis will be positive so I added another
				variable that will randomly be either 1 or -1 and multiplicate the Y axis
				by it.
			*/
			int neg;
			if((randomNum(2) > 1))
				neg = 1;
			else
				neg = -1;

			grid[x][y].y = (float)sqrt((float)1 - pow(grid[x][y].x,2)) * neg;
		}

}

float getPointHeight(int x,int y){

	float grads[4]; //the four gradients
	Vec corners[4]; //position of the corner vectors
	Vec cornersVectors[4]; //corner vectors

	int cellpxsize; //size in pixel of a single cell
	cellpxsize = round(gridWidth / (nodesxn - 1));
	int gx,gy;

	gx = x / cellpxsize;
	gy = y / cellpxsize;
	
	//cap
	if(gx >= nodesxn - 1)
		gx = nodesxn - 2;
	if(gy >= nodesxn - 1)
		gy = nodesxn - 2;

	//get corners
	corners[0].x = gx * cellpxsize;
	corners[0].y = gy * cellpxsize;

	corners[1].x = gx * cellpxsize + cellpxsize;
	corners[1].y = gy * cellpxsize;

	corners[2].x = gx * cellpxsize;
	corners[2].y = gy * cellpxsize + cellpxsize;

	corners[3].x = gx * cellpxsize + cellpxsize;
	corners[3].y = gy * cellpxsize + cellpxsize;

	//get corners vectors
	cornersVectors[0] = grid[gx][gy];
	cornersVectors[1] = grid[gx+1][gy];
	cornersVectors[2] = grid[gx][gy+1];
	cornersVectors[3] = grid[gx+1][gy+1];

	for(int i = 0; i < 4; i++){

		Vec offset; //get offset vector
		offset.x = corners[i].x - x;
		offset.y = corners[i].y - y;

		normalizeVec(&offset,cellpxsize); //normalize it

		grads[i] = dot(offset,cornersVectors[i]); //calculate gradient

	}

	float i1 = interpolate((float)(x - corners[0].x)/cellpxsize,grads[0],grads[1]);
	float i2 = interpolate((float)(x - corners[2].x)/cellpxsize,grads[2],grads[3]);

	return interpolate((float)(y - corners[0].y)/cellpxsize,i1,i2);
}

float randomNum(float max){

	return ((float)rand()/(float)(RAND_MAX)) * max;
	
}

float dot(Vec v1,Vec v2){
	
	return v1.x * v2.x + v1.y * v2.y;
	
}

float interpolate(float t, float a, float b)
{

	// linear interpolation:
	//return a + t*( b - a );

	//cosine interpolation
	float t2 = (1 - cos(t*3.1415926)) /2;
	return (a*(1-t2)+b*t2);

	// smooth interpolation
	//return (b - a) * (3.0 - t * 2.0) * t * t + a; 

	//even smoother interpolation
	//return (b - a) * ((t * (t * 6.0 - 15.0) + 10.0) * t * t * t) + a; 
}

void normalizeVec( Vec* p ,int max)
{
	p->x /= max;
	p->y /= max;
}

void clearPerlinVectors(){

	for(int i = 0; i < nodesxn; i++)
		free(grid[i]);
	free(grid);

}

Vec **getGrid(){
	return grid;
}