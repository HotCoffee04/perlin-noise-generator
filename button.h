#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

typedef struct Button{

	int clicked; 
	SDL_Texture *regular;
	SDL_Texture *pressed;
	SDL_Rect transform;
	void (*pressd)(SDL_Renderer*); //button press function

}Button;


Button* createButton(SDL_Renderer *rend,void *texData,void *tex2Data,int texSize,int tex2Size,SDL_Rect rect,void (*pressfunc)(SDL_Renderer*));

//draw button to renderer
void drawButton(SDL_Renderer *rend, Button *b);

//checks if coordinates are inside the button
int hoveringCheckButton(Button *b,int x,int y);

//free button memory
void destroyButton(Button *b);

