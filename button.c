#include "button.h"

Button* createButton(SDL_Renderer *rend,void *texData,void *tex2Data,int texSize,int tex2Size,SDL_Rect rect,void (*pressfunc)(SDL_Renderer*)){

	Button *but = malloc(sizeof(Button));

	SDL_RWops *ops = SDL_RWFromMem(texData,texSize);

	SDL_Surface *surf = IMG_Load_RW(ops,0);

	but->regular = SDL_CreateTextureFromSurface(rend,surf);

	SDL_FreeSurface(surf);
	SDL_RWclose(ops);

	ops = SDL_RWFromMem(tex2Data,tex2Size);
	surf = IMG_Load_RW(ops,0);

	but->pressed = SDL_CreateTextureFromSurface(rend,surf);

	SDL_FreeSurface(surf);
	SDL_RWclose(ops);

	but->pressd = pressfunc;

	but->transform = rect;

	but->clicked = 0;

	return but;
}

void drawButton(SDL_Renderer *rend, Button *b){

	if(b->clicked){
		SDL_RenderCopy(rend,b->pressed,0,&b->transform);
		b->clicked--;
	}else
		SDL_RenderCopy(rend,b->regular,0,&b->transform);
}

int hoveringCheckButton(Button *b,int x,int y){

	int i = 1;

	if(x > b->transform.x + b->transform.w || x < b->transform.x)
		i = 0;
	if(y > b->transform.y + b->transform.h || y < b->transform.y)
		i = 0;

	return i;
}

void destroyButton(Button *b){

	SDL_DestroyTexture(b->regular);
	SDL_DestroyTexture(b->pressed);

	free(b);
}