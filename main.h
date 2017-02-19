#ifndef MAIN_H
#define MAIN_H

#define TAILLE_MAX 1000



///////////////////
// FICHIER SCORE //
///////////////////
/*FILE* fopen(const char* nomDuFichier, const char* modeOuverture);
int fclose(FILE* pointeurSurFichier);
*/

////////////////////////////////
// LES DIFFERENTES STRUCTURES //
////////////////////////////////
typedef enum {False, True} BOOL;	   
typedef enum {empty,pion1,pion2,gutter,wall,prohibited} CASE;
typedef enum {left,right,up_left,up_right,down_left,down_right, no} MOVEMENT;
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

/*
void display_grid();
//void quitSDL();
void pause();
*/


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

#endif
