/*
	Perlin noise with a visual interface implemented with SDL2 in C

	Not a perfect implementation of Perlin Noise, it's just an attempt at
	applying the theory without using pre-made functions.

*/
#define SDL_MAIN_HANDLED 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <time.h>
#include "resources.h"
#include "button.h"
#include "perlin.h"


//original noise size
#define SCREENWIDTH 600
#define SCREENHEIGHT 600

//Perlin grid dimensions (number of cells)
int gridX;
int gridY;

//noise texture
SDL_Texture *noiseTexture;

//draw grid overlay
int drawGrid = 0;

//draw fractal noise
int fractal = 0;

//fractal frequency
float frequency = 0.5;

void toggleGrid(SDL_Renderer *rend);
void toggleFrac(SDL_Renderer *rend);
void decreaseGrid(SDL_Renderer *rend);
void increaseGrid(SDL_Renderer *rend);
void generateNoiseTexture(SDL_Renderer *rend, SDL_Texture *t);

int main(int argc, char *argv[]){
	
	//default size
	gridX = gridY = 10;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		return -1;

	srand(time(NULL));

	//get screen size and calculate scale factor
	SDL_DisplayMode DM;
	SDL_GetDesktopDisplayMode(0, &DM);
	float winScale;
	winScale = ((float)DM.h * 1.5f) / 1080;

	//scaled window size
	int screenwidth = SCREENWIDTH * winScale;
	int screenheight = SCREENHEIGHT * winScale;

	
	SDL_Window *win = SDL_CreateWindow("Perlin Noise",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,screenwidth,screenheight,0);
	SDL_Renderer *rend = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
	SDL_Texture *background;
	SDL_Rect noisePos; //noise texture position and scale
	SDL_Event event;

	//position the texture inside the window
	noisePos.w = screenwidth / 1.5;
	noisePos.h = screenheight / 1.5;

	noisePos.x = screenwidth / 2 - noisePos.w / 2;
	noisePos.y = screenheight / 2.75 - noisePos.h / 2;

	//read background texture from array
	SDL_RWops *ops = SDL_RWFromMem((void*)gb,119788);
	SDL_Surface *surf = IMG_Load_RW(ops,0);
	SDL_RWclose(ops);
	background = SDL_CreateTextureFromSurface(rend,surf);
	SDL_FreeSurface(surf);
	noiseTexture = SDL_CreateTexture(rend,SDL_PIXELFORMAT_RGB888,SDL_TEXTUREACCESS_TARGET,SCREENWIDTH,SCREENHEIGHT);

	///inizialize buttons
	Button *gridBut = createButton(rend,gridb,gridbb,10785,9737,(SDL_Rect){screenwidth/8*2 + 55*winScale - (160*winScale)/2,screenheight/4*3,160*winScale,60*winScale},toggleGrid);
	Button *fracBut = createButton(rend,fracb,fracbb,11195,10062,(SDL_Rect){screenwidth/4*3 - 55 *winScale - (160*winScale)/2,screenheight/4*3,160*winScale,60*winScale},toggleFrac);
	Button *plusBut = createButton(rend,plusb,plusbb,7064,6573,(SDL_Rect){screenwidth/2 - (55*winScale)/2 - winScale * 30   ,screenheight/8*7,55*winScale,55*winScale},increaseGrid);
	Button *minusBut = createButton(rend,minusb,minusbb,6356,6054,(SDL_Rect){screenwidth/2 - (55*winScale)/2 + winScale * 30  ,screenheight/8*7,55*winScale,55*winScale},decreaseGrid);

	//generate perlin
	generateNoiseTexture(rend,noiseTexture);

	int close = 0;
	while(!close){

		SDL_RenderClear(rend);
		SDL_RenderCopy(rend,background,0,0);
		SDL_RenderCopy(rend,noiseTexture,0,&noisePos);

		if(drawGrid){

			//draw grid overlay and vectors
			float cellSize = (float)noisePos.w / (float)gridX;
			Vec **grid = getGrid();

			SDL_SetRenderDrawColor(rend,0,0,255,255);

			for(int i = 0; i< gridX + 1; i++)
			SDL_RenderDrawLine(rend,noisePos.x + i*cellSize,noisePos.y,noisePos.x+i * cellSize,noisePos.y+noisePos.h);

			for(int j = 0; j < gridY + 1; j++)
				SDL_RenderDrawLine(rend,noisePos.x,noisePos.y + j * cellSize,noisePos.x + noisePos.w,noisePos.y+j * cellSize);

			SDL_SetRenderDrawColor(rend,255,0,0,255);
			for(int i = 0; i< gridX + 1; i++){
				for(int j = 0; j < gridY + 1; j++){
					SDL_RenderDrawLine(rend,noisePos.x + i * cellSize,noisePos.y + j*cellSize, noisePos.x + i * cellSize + grid[i][j].x * cellSize/2, noisePos.y + j*cellSize+ grid[i][j].y * cellSize/2);
				}
			}

			SDL_RenderPresent(rend);
		}


		drawButton(rend,gridBut);
		drawButton(rend,fracBut);
		drawButton(rend,plusBut);
		drawButton(rend,minusBut);

		SDL_RenderPresent(rend);
		int x,y;
		while(SDL_PollEvent(&event)){

			switch(event.type){
				case SDL_QUIT:
					close = 1;
				break;
				case SDL_KEYDOWN:
					if(event.key.keysym.scancode == SDL_SCANCODE_UP && frequency < 1){
						frequency += 0.1;
						generateNoiseTexture(rend,noiseTexture);
					}else if(event.key.keysym.scancode == SDL_SCANCODE_DOWN && frequency > 0.1){
						frequency -= 0.1;
						generateNoiseTexture(rend,noiseTexture);
					}

				break;
				case SDL_MOUSEBUTTONDOWN:

					SDL_GetMouseState(&x,&y);

					//check if buttons are pressed
					if(hoveringCheckButton(gridBut,x,y)){
						gridBut->clicked = 3;
						gridBut->pressd(rend);
					}
					if(hoveringCheckButton(plusBut,x,y)){
						plusBut->clicked = 3;
						plusBut->pressd(rend);
					}
					if(hoveringCheckButton(minusBut,x,y)){
						minusBut->clicked = 3;
						minusBut->pressd(rend);
					}
					if(hoveringCheckButton(fracBut,x,y)){
						fracBut->clicked = 3;
						fracBut->pressd(rend);
					}

				break;
			}


		}
		SDL_Delay(1000 / 30); //30 fps per second

	}

	//clean up
	clearPerlinVectors();
	destroyButton(gridBut);
	destroyButton(plusBut);
	destroyButton(minusBut);
	SDL_DestroyTexture(noiseTexture);
	SDL_DestroyTexture(background);
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(rend);
	SDL_Quit();
	return 0;
}

void generateNoiseTexture(SDL_Renderer *rend, SDL_Texture *t){

	if(!t || !rend)
		return;

	//generate random vectors
	generatePerlinVectors(gridX,gridY);

	SDL_SetRenderTarget(rend,t); //draw to texture from now on

	SDL_RenderClear(rend);

	getPointHeight(5,5);

	float height;
	for(float x = 0; x < SCREENWIDTH; x++){

		for(float y = 0; y < SCREENHEIGHT; y++){

			//normalize X and Y to a maximum of GridX and GridY
			float nx = x * gridX / SCREENWIDTH;
			float ny = y * gridY / SCREENHEIGHT;

			if(fractal)
				height = getFractalPointHeight(nx,ny,4,1,frequency) - 1;
			else
				height = getPointHeight(nx,ny); //get height of that point

			if(height < -1)
				height = -0.99;
			if(height > 1)
				height = 0.99;

			//normalize height
			height += 1.0f;
			height = height * 255 / 2;

			//draw pixel
			SDL_SetRenderDrawColor(rend,height,height,height,255);
			SDL_RenderDrawPoint(rend,x,y);
			
		}

	}

	SDL_RenderPresent(rend);

	SDL_SetRenderTarget(rend,0); //draw to window from now on
}


void toggleGrid(SDL_Renderer *rend){
	if(!fractal)
	drawGrid = !drawGrid;
}

void increaseGrid(SDL_Renderer *rend){

	//if we are viewing the regular perlin noise
	//we increate the noise grid, otherwise we increase the
	//fractal frequency

	if(fractal){
		if(frequency < 1)
			frequency+=0.1f;

	}else
	if(gridX < 50){
		gridX+=1;
		gridY+=1;
	}

	generateNoiseTexture(rend,noiseTexture);
}

void decreaseGrid(SDL_Renderer *rend){

	if(fractal){
		if(frequency > 0.1)
			frequency-=0.1;

	}else
	if(gridX > 1){
		gridX-=1;
		gridY-=1;
	}

	generateNoiseTexture(rend,noiseTexture);
}


void toggleFrac(SDL_Renderer *rend){
	fractal = !fractal;
	generateNoiseTexture(rend,noiseTexture);
	drawGrid = 0;
}