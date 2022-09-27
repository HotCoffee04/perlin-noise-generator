typedef struct Vec{
	
	float x;
	float y;
	
}Vec;

/*
	Inizializes the grid as an array of vectors and randomly inizializes them\
	Needs to be called before getPointHeight() or getFractalPointHeight()
*/
void generatePerlinVectors(int cellsxn,int cellsyn);

/*
	returns the height of a point at some specific coordinates
*/
float getPointHeight(float x,float y);

/*
	takes a point on the perlin map and calculates the fractal height
*/
float getFractalPointHeight(float x,float y,int octaves,float amplitude,float frequency);

// frees the grid pointer
void clearPerlinVectors();

//returns the grid pointer
Vec **getGrid();

