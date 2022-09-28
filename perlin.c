#include "perlin.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Vec **grid; 
int nodesxn; //grid width in nodes
int nodesyn; //grid height in nodes

float dot(Vec v1,Vec v2); //Dot product of two vectors
float randomNum(float max); //generates random float from 0 to max
float interpolate(float t, float a, float b);

void generatePerlinVectors(int cellsxn,int cellsyn){
		
	if(grid != 0)
		clearPerlinVectors();

	nodesxn = ++cellsxn;
	nodesyn = ++cellsyn;
	
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


	//after we generated the vectors I need to make them identical on the corners of the grid.
	//In this way the noise will be seamless.
	//This is necessary to make fractal noise
	for(int y = 0; y < nodesyn; y++){
		grid[nodesyn - 1][y] = grid[0][y];
	}
	for(int x = 0; x < nodesxn - 1; x++){
		grid[x][nodesxn - 1] = grid[x][0];

	}
	
	grid[nodesxn - 1][nodesyn - 1] = grid[0][nodesyn - 1] = grid[nodesxn - 1][0] = grid[0][0];

}

float getPointHeight(float x,float y){

	float grads[4]; //the four gradients
	Vec corners[4]; //position of the corner vectors
	Vec cornersVectors[4]; //corner vectors

	int ix,iy;

	ix = x;
	iy = y;
	
	//cap
	if(ix >= nodesxn - 1)
		ix = nodesxn - 2;
	if(iy >= nodesxn - 1)
		iy = nodesxn - 2;

	//get corners
	corners[0].x = ix;
	corners[0].y = iy;

	corners[1].x = ix + 1;
	corners[1].y = iy;

	corners[2].x = ix;
	corners[2].y = iy + 1;

	corners[3].x = ix + 1;
	corners[3].y = iy + 1;

	//get corners vectors
	cornersVectors[0] = grid[ix][iy];
	cornersVectors[1] = grid[ix+1][iy];
	cornersVectors[2] = grid[ix][iy+1];
	cornersVectors[3] = grid[ix+1][iy+1];

	for(int i = 0; i < 4; i++){

		Vec offset; //get offset vector
		offset.x = corners[i].x - x;
		offset.y = corners[i].y - y;

		grads[i] = dot(offset,cornersVectors[i]); //calculate gradient

	}

	float i1 = interpolate((float)(x - corners[0].x),grads[0],grads[1]);
	float i2 = interpolate((float)(x - corners[2].x),grads[2],grads[3]);

	return interpolate((float)(y - corners[0].y),i1,i2);;
}

float getFractalPointHeight(float x,float y,int octaves,float amplitude,float frequency){

	//This is the function for the fractal noise, I will try to explain what I understood so far

	//The first term we see is "octaves", it's a musical term
	// "the interval between one musical pitch and another with double its frequency."
	//However octaves in this context is the number of times we are going to apply the noise
	//to itself

	//The second term is amplitude, normally it should be half the maximum height of a point in the
	//noise, increasing it will make the transition from the maximum height to the minimum height shorter.
	//increasing it in a noise-generated terrain would turn hills into mountains (BUT THE MAXIMUM HEIGHT WOULD STILL BE THE SAME)

	//the frequency is the zoom

	float elevation = amplitude;

	//adds noise to itself
	for(int i = 0;i<octaves;i++){

		float sx = x * frequency;
		float sy = y * frequency;


		while(sx > nodesxn - 1){
			sx = sx - (nodesxn - 1);
		}
		while(sy > nodesyn - 1){
			sy = sy - (nodesyn - 1);
		}

		elevation += getPointHeight(sx,sy) * amplitude;

		//every octave halvs the frequency meaning that each octave
		//makes less and less meaningful changes to the image.
		frequency *= 2;

		amplitude *= 0.5;

	}

	elevation = fmin(2,fmax(elevation,0));

	return elevation;
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

void clearPerlinVectors(){

	for(int i = 0; i < nodesxn; i++)
		free(grid[i]);
	free(grid);

}

Vec **getGrid(){
	return grid;
}