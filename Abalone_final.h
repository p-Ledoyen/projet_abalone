#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#define TAILLE_MAX 1000

int score1=0, score2=0, condition_pion, condition_coup;

///////////////////
// FICHIER SCORE //
///////////////////
FILE* fopen(const char* nomDuFichier, const char* modeOuverture);
int fclose(FILE* pointeurSurFichier);


////////////////////////////////
// LES DIFFERENTES STRUCTURES //
////////////////////////////////
typedef enum {False, True} BOOL;	   
typedef enum {empty,pion1,pion2,gutter,wall,prohibited} CASE;
typedef enum {left,right,up_left,up_right,down_left,down_right} MOVEMENT;
typedef enum {player1,player2} PLAYER;
typedef enum {impossible,line,DL,DR} POSSIBLE; //DL : diagonal left , DR : diagonal right ( on regarde toujours de haut en bas. )
typedef enum {standard,daisy,domination,face_to_face,snake,alliance,labyrinth,aleatoire} START_POSITION;
typedef struct {int x,y;} COORD;
typedef struct DEP_IA_POSSIBLE DEP_IA_POSSIBLE;

struct DEP_IA_POSSIBLE 
{
	COORD p1,p2,p3;
	struct DEP_IA_POSSIBLE * suivant;
};
typedef DEP_IA_POSSIBLE * lc;



///////////////////////////////////////
// LES DIFFERENTS TABLEAUX D'ENTREES //
///////////////////////////////////////

//Tableau vide
CASE T_reference[11][21]=  {{5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5},
				  			{5,5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5,5},
						    {5,5,5,3,5,0,5,0,5,0,5,0,5,0,5,0,5,3,5,5,5},
						    {5,5,3,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,3,5,5},
						    {5,3,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,3,5},
						    {3,5,0,5,0,5,0,5,1,5,1,5,1,5,0,5,0,5,0,5,3},
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
CASE T_domination[11][21]= {{5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5},
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
CASE T_face_to_face[11][21]= {{5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5},
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
				  
//Entrée marguerite
CASE T_daisy[11][21]= {{5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5},
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
//Entrée snake
CASE T_snake[11][21]= {{5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5},
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
//Entrée alliance
CASE T_alliance[11][21]= {{5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5},
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

//Entrée labyrinthe
CASE T_labyrinth[11][21]= {{5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5},
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
CASE T_aleatoire[11][21]= {{5,5,5,5,5,3,5,3,5,3,5,3,5,3,5,3,5,5,5,5,5},
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




//////////////////////////////
// TABLEAU DES VALEURS (IA) //
//////////////////////////////

//Tableau des valeurs de chaque case (pour l'IA)				
int V[11][21]= {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
				{0,0,0,0,0,0,10,0,10,0,10,0,10,0,10,0,0,0,0,0,0},
				{0,0,0,0,0,10,0,50,0,50,0,50,0,50,0,10,0,0,0,0,0},
				{0,0,0,0,10,0,50,0,75,0,75,0,75,0,50,0,10,0,0,0,0},
				{0,0,0,10,0,50,0,75,0,85,0,85,0,75,0,50,0,10,0,0,0},
				{0,0,10,0,50,0,75,0,85,0,100,0,85,0,75,0,50,0,10,0,0},
				{0,0,0,10,0,50,0,75,0,85,0,85,0,75,0,50,0,10,0,0,0},
				{0,0,0,0,10,0,50,0,75,0,75,0,75,0,50,0,10,0,0,0,0},
				{0,0,0,0,0,10,0,50,0,50,0,50,0,50,0,10,0,0,0,0,0},
				{0,0,0,0,0,0,10,0,10,0,10,0,10,0,10,0,0,0,0,0,0},
				{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

///////////////////////////////
// LES DIFFERENTES FONCTIONS //
///////////////////////////////

         //Le modèle
void swap_player();

//////// VERIFICATION MOUVEMENTS ////////
int check_pion_selected_1(COORD p1,CASE T[11][21],PLAYER player);
int check_pion_selected_2(COORD p1,COORD p2,CASE T[11][21],PLAYER player);
int check_pion_selected_3( COORD p1, COORD p2, COORD p3,CASE T[11][21],PLAYER player);


//Pour 1 pion
POSSIBLE move_possible_1( COORD p1, MOVEMENT mov,CASE T[11][21],PLAYER player);
POSSIBLE move_possible_left_1( COORD p1,CASE T[11][21],PLAYER player);
POSSIBLE move_possible_right_1( COORD p1,CASE T[11][21],PLAYER player);
POSSIBLE move_possible_up_left_1( COORD p1,CASE T[11][21],PLAYER player);
POSSIBLE move_possible_up_right_1( COORD p1,CASE T[11][21],PLAYER player);
POSSIBLE move_possible_down_left_1( COORD p1,CASE T[11][21],PLAYER player);
POSSIBLE move_possible_down_right_1( COORD p1,CASE T[11][21],PLAYER player);

//Pour 2 pions
POSSIBLE move_possible_2( COORD p1, COORD p2, MOVEMENT mov,CASE T[11][21],PLAYER player);
POSSIBLE move_possible_left_2( COORD p1, COORD p2,CASE T[11][21],PLAYER player);
POSSIBLE move_possible_right_2( COORD p1, COORD p2,CASE T[11][21],PLAYER player);
POSSIBLE move_possible_up_left_2( COORD p1, COORD p2,CASE T[11][21],PLAYER player);
POSSIBLE move_possible_up_right_2( COORD p1, COORD p2,CASE T[11][21],PLAYER player);
POSSIBLE move_possible_down_left_2( COORD p1, COORD p2,CASE T[11][21],PLAYER player);
POSSIBLE move_possible_down_right_2( COORD p1, COORD p2,CASE T[11][21],PLAYER player);

//Pour 3 pions
POSSIBLE move_possible_3( COORD p1, COORD p2, COORD p3, MOVEMENT mov,CASE T[11][21],PLAYER player);
POSSIBLE move_possible_left_3( COORD p1, COORD p2, COORD p3,CASE T[11][21],PLAYER player);
POSSIBLE move_possible_right_3( COORD p1, COORD p2, COORD p3,CASE T[11][21],PLAYER player);
POSSIBLE move_possible_up_left_3( COORD p1, COORD p2, COORD p3,CASE T[11][21],PLAYER player);
POSSIBLE move_possible_up_right_3( COORD p1, COORD p2, COORD p3,CASE T[11][21],PLAYER player);
POSSIBLE move_possible_down_left_3( COORD p1, COORD p2, COORD p3,CASE T[11][21],PLAYER player);
POSSIBLE move_possible_down_right_3( COORD p1, COORD p2, COORD p3,CASE T[11][21],PLAYER player);     
    
//////// LES MOUVEMENTS ////////
//Mouvements 1 pion
void move_left_1 (COORD p1,CASE T[11][21]);
void move_right_1 (COORD p1,CASE T[11][21]);
void move_up_left_1 (COORD p1,CASE T[11][21]);
void move_up_right_1 (COORD p1,CASE T[11][21]);
void move_down_left_1 (COORD p1,CASE T[11][21]);
void move_down_right_1 (COORD p1,CASE T[11][21]);

//Mouvements 2 pions
void move_left_2 (COORD p1,COORD p2,POSSIBLE alignment,CASE T[11][21]);
void move_right_2 (COORD p1,COORD p2,POSSIBLE alignment,CASE T[11][21]);
void move_up_left_2 (COORD p1, COORD p2,POSSIBLE alignment,CASE T[11][21]);
void move_up_right_2 (COORD p1, COORD p2,POSSIBLE alignment,CASE T[11][21]);
void move_down_left_2 (COORD p1, COORD p2, POSSIBLE alignment,CASE T[11][21]);
void move_down_right_2 (COORD p1, COORD p2,POSSIBLE alignment,CASE T[11][21]);

//Mouvements 3 pions
void move_left_3 (COORD p1,COORD p2,COORD p3,POSSIBLE alignment,CASE T[11][21]);
void move_right_3 (COORD p1,COORD p2,COORD p3,POSSIBLE alignment,CASE T[11][21]);
void move_up_left_3 (COORD p1, COORD p2,COORD p3,POSSIBLE alignment,CASE T[11][21]);
void move_up_right_3 (COORD p1, COORD p2,COORD p3,POSSIBLE alignment,CASE T[11][21]);
void move_down_left_3 (COORD p1, COORD p2,COORD p3,POSSIBLE alignment,CASE T[11][21]);
void move_down_right_3 (COORD p1, COORD p2,COORD p3,POSSIBLE alignment,CASE T[11][21]);


//Coordination des mouvements
void move( COORD p1, COORD p2, COORD p3, MOVEMENT mov, POSSIBLE alignment,CASE T[11][21]);
void move_1( COORD p1, MOVEMENT mov, POSSIBLE alignment,CASE T[11][21]);
void move_2( COORD p1, COORD p2, MOVEMENT mov, POSSIBLE alignment,CASE T[11][21]);
void move_3( COORD p1, COORD p2, COORD p3, MOVEMENT mov, POSSIBLE alignment,CASE T[11][21]);


//////// INITIALISATION DES TABLEAUX ////////
void copy_tab(CASE T_reference[11][21], CASE T_variant[11][21]);
void insert_pion(CASE p);
void aleatoire_tab();
void init_tab (START_POSITION pos);

//////// L'IA ////////
int number_pions(COORD p1, COORD p2, COORD p3);
int value_board(CASE T[11][21],PLAYER player);
int maximum(int a, int b);
int minimum(int a, int b);
lc add_list(lc liste,COORD pos1,COORD pos2,COORD pos3,CASE T[11][21]);
lc gather_pions_possible(CASE T[11][21],PLAYER player);
lc pions_together(lc liste,CASE pawn,int l,int c,CASE T[11][21]);
lc pions_together_inverse(lc liste,CASE pawn,int l,int c,CASE T[11][21]);
int Min(CASE T_bis[11][21], int depth, int alpha, int beta, PLAYER player_bis);
int Max(CASE T_bis[11][21], int depth, int alpha, int beta, PLAYER player_bis);
