#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>

#include "main.h"

typedef struct
{
	char key[SDLK_LAST];
	int mousex,mousey;
	int mousexrel,mouseyrel;
	char mousebuttons[8];
	char quit;
	double w, h;
} Input;

void display_grid(CASE T[11][21]);
void UpdateEvents(Input* in);
void display_grid(CASE T[11][21]);
COORD square_calculation(Input in, CASE T_daisy[11][21]);
void display_move_possible_1(COORD c,CASE T[11][21],MOVEMENT move);
void display_move_possible_2(COORD C1, COORD C2, CASE T[11][21], MOVEMENT move);
void display_move_possible_3(COORD C1, COORD C2, COORD C3,CASE T[11][21], MOVEMENT move);
MOVEMENT square_direction(COORD cat[5], int i, int s);
//void quitSDL();
void pause();
