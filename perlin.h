typedef struct Vec{
	
	float x;
	float y;
	
}Vec;

/*
	Inizializes the grid as an array of vectors and randomly inizializes them\
	Needs to be called before getPointHeight()
*/
void generatePerlinVectors(int cellsxn,int cellsyn,float gridWidth,float gridHeight);

/*
	returns the height of a point at some specific coordinates
*/
float getPointHeight(int x,int y);

// frees the grid pointer
void clearPerlinVectors();

//returns the grid pointer
Vec **getGrid();

