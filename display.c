
#include "display.h"

void display_move_possible_1(COORD C,CASE T[11][21], MOVEMENT move)
{
	int r=C.x;
	int c=C.y;
	SDL_Surface *ecran = SDL_GetVideoSurface();
	int width_margin_even=283, width_margin_odd=319, height_margin=320;
	SDL_Rect positionPion;
	SDL_Surface *imagePionP1 = NULL, *imagePionP2 = NULL, *imageCase = IMG_Load("case_vide.png");
	if(move==left)
	{
		imagePionP1=IMG_Load("v_g.png");
		imagePionP2=IMG_Load("b_g.png");
		
	}
	else if(move==right)
	{
		imagePionP1=IMG_Load("v_d.png");
		imagePionP2=IMG_Load("b_d.png");
	}
	else if(move==up_left)
	{
		imagePionP1=IMG_Load("v_hg.png");
		imagePionP2=IMG_Load("b_hg.png");
	}
	else if(move==up_right)
	{
		imagePionP1=IMG_Load("v_hd.png");
		imagePionP2=IMG_Load("b_hd.png");
	}
	else if(move==down_left)
	{
		imagePionP1=IMG_Load("v_bg.png");
		imagePionP2=IMG_Load("b_bg.png");
	}
	else if(move==down_right)
	{
		imagePionP1=IMG_Load("v_bd.png");
		imagePionP2=IMG_Load("b_bd.png");
	}
	else if(move==no)
	{
		imagePionP1=IMG_Load("v.png");
		imagePionP2=IMG_Load("b.png");
	}
	
	imagePionP1=shrinkSurface(imagePionP1,2,2);
	imagePionP2=shrinkSurface(imagePionP2,2,2);
	imageCase=shrinkSurface(imageCase,2,2);
	
	
	positionPion.y=height_margin+(r-1)*59;
	
	if(c%2==0)
	{
		positionPion.x=width_margin_even+71*(c-2)/2;
	}
	else
	{
		positionPion.x=width_margin_odd+71*(c-3)/2;
	}
	if(T[r][c]==1)
	{
		SDL_BlitSurface(imageCase, NULL, ecran, &positionPion);
		SDL_BlitSurface(imagePionP1, NULL, ecran, &positionPion);
	}
	else if (T[r][c]==2)
	{
		SDL_BlitSurface(imageCase, NULL, ecran, &positionPion);
		SDL_BlitSurface(imagePionP2, NULL, ecran, &positionPion);
	
	}
	SDL_Flip(ecran);
}

void display_move_possible_2(COORD C1, COORD C2,CASE T[11][21], MOVEMENT move)
{
	display_move_possible_1(C1,T,move);
	display_move_possible_1(C2,T,move);
}
void display_move_possible_3(COORD C1, COORD C2, COORD C3,CASE T[11][21], MOVEMENT move)
{
	display_move_possible_1(C1,T,move);
	display_move_possible_1(C2,T,move);
	display_move_possible_1(C3,T,move);
}

COORD square_calculation(Input in, CASE T_daisy[11][21])
{
	COORD P;
	int width_margin_even=283, width_margin_odd=319, height_margin=320;
	P.x=((in.mousey-height_margin)/59)+1; //ligne
	P.x=(int)P.x;
	if(P.x%2==0) //si la ligne est paire, la colonne est impaire
	{
		P.y=(2*(in.mousex-width_margin_odd)/72)+3;
	}
	else
	{
		P.y=(2*(in.mousex-width_margin_even)/72)+2;
		
	}
	P.y=(int)P.y;
	if(T_daisy[P.x][P.y]==5 || T_daisy[P.x][P.y]==3) //décalage si on tombe dans une case hors jeu
	{
		(P.y)--;
	}
	return P;
}


MOVEMENT square_direction(COORD cat[5], int i, int s)
	{
		MOVEMENT d=no;
		for(int e=i; e<s; e++)
		{
			if((cat[e+1].x==cat[e].x && cat[e+1].y==cat[e].y-2) && (d==left || (d=no && e==0)))
				d=left;
			
			else if((cat[e+1].x==cat[e].x && cat[e+1].y==cat[e].y+2) && (d==right || (d==no && e==0)))
				d=right;
				
			else if((cat[e+1].x==cat[e].x-1 && cat[e+1].y==cat[e].y-1) && (d==up_left || (d==no && e==0)))
				d=up_left;
				
			else if((cat[e+1].x==cat[e].x-1 && cat[e+1].y==cat[e].y+1) && (d==up_right || (d==no && e==0)))
				d=up_right;
				
			else if((cat[e+1].x==cat[e].x+1 && cat[e+1].y==cat[e].y-1) && (d==down_left || (d==no && e==0)))
				d=down_left;
			
			else if((cat[e+1].x==cat[e].x+1 && cat[e+1].y==cat[e].y+1) && (d==down_right || (d==no && e==0)))
				d=down_right;
			
			else 
				d=no;
		}
		return d;
	}

void UpdateEvents(Input* in)
{
	SDL_Event event;
        in->mousebuttons[SDL_BUTTON_WHEELUP] = 0;
        in->mousebuttons[SDL_BUTTON_WHEELDOWN] = 0;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			in->key[event.key.keysym.sym]=1;
			break;
		case SDL_KEYUP:
			in->key[event.key.keysym.sym]=0;
			break;
		case SDL_MOUSEMOTION:
			in->mousex=event.motion.x;
			in->mousey=event.motion.y;
			in->mousexrel=event.motion.xrel;
			in->mouseyrel=event.motion.yrel;
			break;
		case SDL_MOUSEBUTTONDOWN:
			in->mousebuttons[event.button.button]=1;
			break;
		case SDL_MOUSEBUTTONUP:
                        if (event.button.button!=SDL_BUTTON_WHEELUP && event.button.button!=SDL_BUTTON_WHEELDOWN)
			   in->mousebuttons[event.button.button]=0;
			break;
		case SDL_QUIT:
			in->quit = 1;
			break;
		case SDL_VIDEORESIZE:
				in->w = event.resize.w;
				in->h = event.resize.h;
		default:
			break;
		}
	}
}

void display_grid(CASE T[11][21])
{
	SDL_Surface *ecran = SDL_GetVideoSurface();
	int width_margin_even=283, width_margin_odd=319, height_margin=320;
	SDL_Rect positionPion;
	SDL_Surface *imagePionP1 = NULL, *imagePionP2 = NULL, *imagePionV = NULL;
	imagePionP1=IMG_Load("v.png");
	imagePionP2=IMG_Load("b.png");
	imagePionV=IMG_Load("case_vide.png");
	imagePionP1=shrinkSurface(imagePionP1,2,2);
	imagePionP2=shrinkSurface(imagePionP2,2,2);
	imagePionV=shrinkSurface(imagePionV,2,2);
	for(int r=1; r<10; r++)
	{
		positionPion.y=height_margin+(r-1)*59;
		for(int c=2; c<19; c++)
		{
			
			if(c%2==0)
			{
				positionPion.x=width_margin_even+71*(c-2)/2;
			}
			else
			{
				positionPion.x=width_margin_odd+71*(c-3)/2;
			}
			if(T[r][c]==1)
			{
				
				SDL_BlitSurface(imagePionP1, NULL, ecran, &positionPion);
			}
			else if (T[r][c]==2)
			{
				SDL_BlitSurface(imagePionP2, NULL, ecran, &positionPion);
			
			}
			else if (T[r][c]==0)
			{
				SDL_BlitSurface(imagePionV, NULL, ecran, &positionPion);
			}
		}
		SDL_Flip(ecran);
	}
    
}


/*void quitSDL()
{
	SDL_FreeSurface(imageDeFond);
    SDL_Quit();
}*/
 
void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
