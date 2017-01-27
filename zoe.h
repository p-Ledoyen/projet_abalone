#include <stdio.h>
		   
typedef enum {free,p1,p2,gutter,wall,prohibited} CASE;
typedef enum {left,right,up_left,up_right,down_left,down_right} DEPLACEMENT;
typedef enum {player1,player2} TURN;
typedef enum {impossible,line,DL,DR} POSSIBLE;
typedef enum {standard,daisy,domination,face_to_face,snake,alliance,labyrinth,random} START_POSITION;
typedef struct {int x,y;} COORD;

//Tableau vide
CASE T[11][21]=			 {{5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5},
				  {5,5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5,5},
				  {5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5},
				  {5,5,3,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,3,5,5},
				  {5,3,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,3,5},
				  {3,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,3},
				  {5,3,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,3,5},
				  {5,5,3,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,3,5,5},
				  {5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5},
				  {5,5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5,5},
				  {5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5}};
				
//Entrée standard
CASE T_standard[11][21]= {{5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5},
						  {5,5,5,5,3,5,2,5,2,5,2,5,2,5,2,5,3,5,5,5,5},
						  {5,5,5,3,5,2,5,2,5,2,5,2,5,2,5,2,5,3,5,5,5},
						  {5,5,3,5,0,5,0,5,2,5,2,5,2,5,0,5,0,5,3,5,5},
						  {5,3,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,3,5},
						  {3,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,3},
						  {5,3,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,3,5},
						  {5,5,3,5,0,5,0,5,1,5,1,5,1,5,0,5,0,5,3,5,5},
						  {5,5,5,3,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,5,5},
						  {5,5,5,5,3,5,1,5,1,5,1,5,1,5,1,5,3,5,5,5,5},
						  {5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5}};	

//Entrée domination
CASE T_domination[11][21]={{5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5},
						   {5,5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5,5},
						   {5,5,5,3,5,2,5,0,5,0,5,0,5,0,5,1,5,3,5,5,5},
						   {5,5,3,5,2,5,2,5,0,5,0,5,0,5,1,5,1,5,3,5,5},
						   {5,3,5,2,5,2,5,2,5,2,5,0,5,1,5,1,5,1,5,3,5},
						   {3,5,0,5,0,5,0,5,1,5,0,5,1,5,0,5,0,5,0,5,3},
						   {5,3,5,1,5,1,5,1,5,0,5,2,5,2,5,2,5,2,5,3,5},
						   {5,5,3,5,1,5,1,5,0,5,0,5,0,5,2,5,2,5,3,5,5},
						   {5,5,5,3,5,1,5,0,5,0,5,0,5,0,5,2,5,3,5,5,5},
						   {5,5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5,5},
						   {5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5}};
				  
//Entrée face à face
CASE T_face_to_face[11][21]=  {{5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5},
							  {5,5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5,5},
							  {5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5},
							  {5,5,3,5,2,5,2,5,0,5,0,5,0,5,1,5,1,5,3,5,5},
							  {5,3,5,2,5,2,5,2,5,0,5,0,5,1,5,1,5,1,5,3,5},
							  {3,5,2,5,2,5,2,5,2,5,0,5,1,5,1,5,1,5,1,5,3},
							  {5,3,5,2,5,2,5,2,5,0,5,0,5,1,5,1,5,1,5,3,5},
							  {5,5,3,5,2,5,2,5,0,5,0,5,0,5,1,5,1,5,3,5,5},
							  {5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5},
							  {5,5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5,5},
							  {5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5}};
				  
//Entrée Marguerite
CASE T_daisy[11][21]={{5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5},
						   {5,5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5,5},
						   {5,5,5,3,5,2,5,2,5,0,5,0,5,1,5,1,5,3,5,5,5},
						   {5,5,3,5,2,5,1,5,2,5,0,5,1,5,2,5,1,5,3,5,5},
						   {5,3,5,0,5,2,5,2,5,0,5,0,5,1,5,1,5,0,5,3,5},
						   {3,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,3},
						   {5,3,5,0,5,1,5,1,5,0,5,0,5,2,5,2,5,0,5,3,5},
						   {5,5,3,5,1,5,2,5,1,5,0,5,2,5,1,5,2,5,3,5,5},
						   {5,5,5,3,5,1,5,1,5,0,5,0,5,2,5,2,5,3,5,5,5},
						   {5,5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5,5},
						   {5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5}};
//Entrée Snake
CASE T_snake[11][21]={{5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5},
				  {5,5,5,5,3,5,1,5,1,5,1,5,1,5,1,5,3,5,5,5,5},
				  {5,5,5,3,5,1,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5},
				  {5,5,3,5,1,5,0,5,0,5,0,5,0,5,0,5,0,5,3,5,5},
				  {5,3,5,1,5,0,5,0,5,1,5,1,5,2,5,2,5,0,5,3,5},
				  {3,5,0,5,1,5,0,5,1,5,0,5,2,5,0,5,2,5,0,5,3},
				  {5,3,5,0,5,1,5,1,5,2,5,2,5,0,5,0,5,2,5,3,5},
				  {5,5,3,5,0,5,0,5,0,5,0,5,0,5,0,5,2,5,3,5,5},
				  {5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,2,5,3,5,5,5},
				  {5,5,5,5,3,5,2,5,2,5,2,5,2,5,2,5,3,5,5,5,5},
				  {5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5}};
//Entrée Alliance
CASE T_alliance[11][21]= 	 {{5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5},
				  {5,5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5,5},
				  {5,5,5,3,5,0,5,2,5,2,5,1,5,1,5,0,5,3,5,5,5},
				  {5,5,3,5,0,5,2,5,0,5,2,5,1,5,1,5,0,5,3,5,5},
				  {5,3,5,0,5,2,5,0,5,1,5,2,5,0,5,1,5,0,5,3,5},
				  {3,5,0,5,2,5,0,5,1,5,0,5,2,5,0,5,1,5,0,5,3},
				  {5,3,5,0,5,2,5,0,5,1,5,2,5,0,5,1,5,0,5,3,5},
				  {5,5,3,5,0,5,2,5,2,5,1,5,0,5,1,5,0,5,3,5,5},
				  {5,5,5,3,5,0,5,2,5,2,5,1,5,1,5,0,5,3,5,5,5},
				  {5,5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5,5},
				  {5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5}};

//Entrée Labyrinthe
CASE T_labyrinth[11][22]=       {{5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5},
				  {5,5,5,5,3,5,0,5,0,5,1,5,2,5,1,5,3,5,5,5,5},
				  {5,5,5,3,5,0,5,2,5,0,5,0,5,0,5,1,5,3,5,5,5},
				  {5,5,3,5,0,5,2,5,1,5,2,5,0,5,0,5,1,5,3,5,5},
				  {5,3,5,0,5,2,5,0,5,0,5,2,5,0,5,0,5,2,5,3,5},
				  {3,5,0,5,2,5,0,5,1,5,0,5,2,5,0,5,1,5,0,5,3},
				  {5,3,5,1,5,0,5,0,5,1,5,0,5,0,5,1,5,0,5,3,5},
				  {5,5,3,5,2,5,0,5,0,5,1,5,2,5,1,5,0,5,3,5,5},
				  {5,5,5,3,5,2,5,0,5,0,5,0,5,1,5,0,5,3,5,5,5},
				  {5,5,5,5,3,5,2,5,1,5,2,5,0,5,0,5,3,5,5,5,5},
				  {5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5}};

//Entrée random
CASE T_random[11][21]={{5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5},
				  {5,5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5,5},
				  {5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5},
				  {5,5,3,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,3,5,5},
				  {5,3,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,3,5},
				  {3,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,3},
				  {5,3,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,3,5},
				  {5,5,3,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,3,5,5},
				  {5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5},
				  {5,5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5,5},
				  {5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5}};
						    

