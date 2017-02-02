#include "Abalone_final.h"	  
 
//Variables globales 
PLAYER current_player = player1;

//Change de joueur :
void swap_player()
{
	if (current_player==player1)
		current_player=player2;
	else
		current_player=player1;
}

// VERIFICATION DES MOUVEMENTS 
POSSIBLE move_possible( COORD p1, COORD p2, COORD p3, MOVEMENT mov,CASE T[11][21],PLAYER player)
{
	int nb;
	nb = number_pions(p1, p2, p3);
	switch(nb)
	{
		case 1 : return move_possible_1( p1,mov,T,player);
			break;
		case 2 : return move_possible_2( p1, p2, mov,T,player);
			break;
		case 3 : return move_possible_3( p1, p2, p3, mov,T,player);
			break;
		default : return impossible;
			break;
	}
}

//Cas 1 pion.
POSSIBLE move_possible_1(COORD p1, MOVEMENT mov, CASE T[11][21],PLAYER player)
{
	int V;
	V = check_pion_selected_1(p1,T,player);
	//Si l'entier T est à 0, alors tous les pions sélectionnés appartiennent au bon joueur, on peut donc vérifier si le déplacement est autorisé.
	if (V==0)
	{
		switch(mov)
		{
			case left : return move_possible_left_1(p1,T,player); 
				break;
			case right : return move_possible_right_1(p1,T,player); 
				break;
			case up_left : return move_possible_up_left_1(p1,T,player); 	
				break;
			case up_right : return move_possible_up_right_1(p1,T,player); 
				break;
			case down_left : return move_possible_down_left_1(p1,T,player); 
				break;
			case down_right : return move_possible_down_right_1(p1,T,player); 
				break;
			default : return impossible;
				break;
		}
	}
}
 
int check_pion_selected_1(COORD p1,CASE T[11][21],PLAYER player)
{
	if ( (player==player1) && (T[p1.x][p1.y]==pion1) ) return 0;
	else if ((player==player2) && (T[p1.x][p1.y]== pion2)  ) return 0;
	else return 1;
}

POSSIBLE move_possible_left_1(COORD p1,CASE T[11][21],PLAYER player)
{
	if (T[p1.x][p1.y-2]==empty) return line;
	else return impossible;
}

POSSIBLE move_possible_right_1(COORD p1,CASE T[11][21],PLAYER player)
{
	if (T[p1.x][p1.y+2]==empty) return line;
	else return impossible;
}

POSSIBLE move_possible_up_left_1(COORD p1,CASE T[11][21],PLAYER player)
{
	if (T[p1.x-1][p1.y-1]==empty) return line;
	else return impossible;
}

POSSIBLE move_possible_up_right_1(COORD p1,CASE T[11][21],PLAYER player)
{
	if (T[p1.x-1][p1.y+1]==empty) return line;
	else return impossible;
}

POSSIBLE move_possible_down_left_1(COORD p1,CASE T[11][21],PLAYER player)
{
	if (T[p1.x+1][p1.y-1]==empty) return line;
	else return impossible;
}

POSSIBLE move_possible_down_right_1(COORD p1,CASE T[11][21],PLAYER player)
{
	if (T[p1.x+1][p1.y+1]==empty) return line;
	else return impossible;
}

//Cas 2 pions. (On considère que p1 est forcément le premier pion cliqué et p2 dans sa continuité directe).
POSSIBLE move_possible_2(COORD p1,COORD p2,MOVEMENT mov,CASE T[11][21],PLAYER player)
{
	int V;
	V = check_pion_selected_2(p1,p2,T,player);
	//Si l'entier T est à 0, alors tous les pions sélectionnés appartiennent au bon joueur, on peut donc vérifier si le déplacement est autorisé.
	if (V==0)
	{
		switch(mov)
		{
			case left : return move_possible_left_2(p1,p2,T,player); 
				break;
			case right : return move_possible_right_2(p1,p2,T,player); 
				break;
			case up_left : return move_possible_up_left_2(p1,p2,T,player); 	
				break;
			case up_right : return move_possible_up_right_2(p1,p2,T,player); 
				break;
			case down_left : return move_possible_down_left_2(p1,p2,T,player); 
				break;
			case down_right : return move_possible_down_right_2(p1,p2,T,player); 
				break;
			default : return impossible;
				break;
		}
	}
}

int check_pion_selected_2(COORD p1,COORD p2,CASE T[11][21],PLAYER player)
{
	if ( (player==player1) && (T[p1.x][p1.y]==pion1) && (T[p2.x][p2.y]==pion1)  ) return 0;
	else if ((player==player2) && (T[p1.x][p1.y]==pion2) && (T[p2.x][p2.y]==pion2)  ) return 0;
	else return 1;
}

POSSIBLE move_possible_left_2(COORD p1,COORD p2,CASE T[11][21],PLAYER player)
{
	if (p1.x==p2.x) //Les pions sont sur la même lignes, on verrifie donc s'il y a un sumito ou si la case à gauche est vide.
	{
		if ((T[p1.x][p2.y-2]==empty) || ((((player==player1) && (T[p1.x][p2.y-2]==pion2))||((player==player2) && (T[p1.x][p2.y-2]==pion1))) && ((T[p1.x][p2.y-4]==empty) || (T[p1.x][p2.y-4]==gutter))) ) return line;
		else return impossible;
	}
	else if (((p1.x==p2.x-1) && (p1.y==p2.y+1)) || ((p1.x==p2.x+1) && (p1.y==p2.y-1))) //Les pions sont en diagonales gauches, on verrifie donc que les 3 cases à gauche sont vides.
	{
		if ( (T[p1.x][p1.y-2]==empty) && (T[p2.x][p2.y-2]==empty) ) return DL;
		else return impossible;
	}
	else if (((p1.x==p2.x+1) && (p1.y==p2.y+1)) || ((p1.x==p2.x-1) && (p1.y==p2.y-1))) //Les pions sont en diagonales droites, on verrifie donc que les 3 cases à gauche sont vides.
	{
		if ( (T[p1.x][p1.y-2]==empty) && (T[p2.x][p2.y-2]==empty) ) return DR;
		else return impossible;
	}
	else return impossible;
}

POSSIBLE move_possible_right_2(COORD p1,COORD p2,CASE T[11][21],PLAYER player)
{
	if (p1.x==p2.x) //Les pions sont sur la même lignes, on verrifie donc s'il y a un sumito ou si la case à gauche est vide.
	{
		if ((T[p1.x][p2.y+2]==empty) || ((((player==player1) && (T[p1.x][p2.y+2]==pion2))||((player==player2) && (T[p1.x][p2.y+2]==pion1))) && ((T[p1.x][p2.y+4]==empty) || (T[p1.x][p2.y+4]==gutter))) ) return line;
		else return impossible;
	}
	else if (((p1.x==p2.x-1) && (p1.y==p2.y+1)) || ((p1.x==p2.x+1) && (p1.y==p2.y-1))) //Les pions sont en diagonales gauches, on verrifie donc que les 3 cases à gauche sont vides.
	{
		if ( (T[p1.x][p1.y+2]==empty) && (T[p2.x][p2.y+2]==empty) ) return DL;
		else return impossible;
	}
	else if (((p1.x==p2.x+1) && (p1.y==p2.y+1)) || ((p1.x==p2.x-1) && (p1.y==p2.y-1))) //Les pions sont en diagonales droites, on verrifie donc que les 3 cases à gauche sont vides.
	{
		if ( (T[p1.x][p1.y+2]==empty) && (T[p2.x][p2.y+2]==empty) ) return DR;
		else return impossible;
	}
	else return impossible;
}

POSSIBLE move_possible_up_left_2( COORD p1, COORD p2,CASE T[11][21],PLAYER player)
{
	if (p1.x==p2.x)  //Les pions sont sur la même lignes, on verrifie donc que les 3 cases en haut à gauche sont vides.
	{
		if ( (T[p1.x-1][p1.y-1]==empty) && (T[p2.x-1][p2.y-1]==empty) ) return line;
		else return impossible;
	}
	else if (( (p1.x==p2.x-1) && (p1.y==p2.y+1) ) || ( (p1.x==p2.x+1) && (p1.y==p2.y-1) )) //Les pions sont en diagonales gauches ( de haut en bas ).
	{
		if ( (T[p1.x-1][p1.y-1]==empty) && (T[p2.x-1][p2.y-1]==empty) ) return DL;
		else return impossible;
	}
	else if ( (p1.x==p2.x+1) && (p1.y==p2.y+1) ) //Les pions sont en diagonales droites ( de haut en bas ).
	{
		if ( (T[p2.x-1][p2.y-1]==empty) || ((((player==player1) && (T[p2.x-1][p2.y-1]==pion2))||((player==player2) && (T[p2.x-1][p2.y-1]==pion1))) && ((T[p2.x-2][p2.y-2]==empty) || (T[p2.x-2][p2.y-2]==gutter))) ) return DR;
		else return impossible;
	}
	else return impossible;
}

POSSIBLE move_possible_up_right_2( COORD p1, COORD p2,CASE T[11][21],PLAYER player)
{
	if (p1.x==p2.x)  //Les pions sont sur la même lignes, on verrifie donc que les 3 cases en haut à droite sont vides.
	{
		if ( (T[p1.x-1][p1.y+1]==empty) && (T[p2.x-1][p2.y+1]==empty) ) return line;
		else return impossible;
	}
	else if ( ((p1.x==p2.x+1) && (p1.y==p2.y+1) ) || ((p1.x==p2.x-1) && (p1.y==p2.y-1) ) ) //Les pions sont en diagonales droites ( de haut en bas ).
	{
		if ( (T[p1.x-1][p1.y+1]==empty) && (T[p2.x-1][p2.y+1]==empty) ) return DR;
		else return impossible;
	}
	else if ((p1.x==p2.x+1) && (p1.y==p2.y-1) ) //Les pions sont en diagonales gauches ( de haut en bas ).
	{
		if ( (T[p2.x-1][p2.y+1]==empty) || ((((player==player1) && (T[p2.x-1][p2.y+1]==pion2))||((player==player2) && (T[p2.x-1][p2.y+1]==pion1))) && ((T[p2.x-2][p2.y+2]==empty) || (T[p2.x-2][p2.y+2]==gutter))) ) return DL;
		else return impossible;
	}
	else return impossible;
}

POSSIBLE move_possible_down_left_2( COORD p1, COORD p2,CASE T[11][21],PLAYER player)
{
	if (p1.x==p2.x) //Les pions sont sur la même lignes, on verrifie donc que les 3 cases en bas à gauche sont vides.
	{
		if ( (T[p1.x+1][p1.y-1]==empty) && (T[p2.x+1][p2.y-1]==empty) ) return line;
		else return impossible;
	}
	else if ( ((p1.x==p2.x+1) && (p1.y==p2.y+1) ) || ((p1.x==p2.x-1) && (p1.y==p2.y-1) ) ) //Les pions sont en diagonales droites ( de haut en bas ).
	{
		if ( (T[p1.x+1][p1.y-1]==empty) && (T[p2.x+1][p2.y-1]==empty) ) return DR;
		else return impossible;
	}
	else if ( (p1.x==p2.x-1) && (p1.y==p2.y+1) ) //Les pions sont en diagonales gauches ( de haut en bas ).
	{
		if ((T[p2.x+1][p2.y-1]==empty) || ((((player==player1) && (T[p2.x+1][p2.y-1]==pion2))||((player==player2) && (T[p2.x+1][p2.y-1]==pion1))) && ((T[p2.x+2][p2.y-2]==empty) || (T[p2.x+2][p2.y-2]==gutter))) ) return DL;
		else return impossible;
	}
	else return impossible;
}

POSSIBLE move_possible_down_right_2( COORD p1, COORD p2,CASE T[11][21],PLAYER player)
{
	if (p1.x==p2.x) //Les pions sont sur la même lignes, on verrifie donc que les 3 cases en haut à gauche sont vides.
	{
		if ( (T[p1.x+1][p1.y+1]==empty) && (T[p2.x+1][p2.y+1]==empty) ) return line;
		else return impossible;
	}
	else if (( (p1.x==p2.x-1) && (p1.y==p2.y+1)  ) || ( (p1.x==p2.x+1) && (p1.y==p2.y-1)  )) //Les pions sont en diagonales gauches ( de haut en bas ).
	{
		if ( (T[p1.x+1][p1.y+1]==empty) && (T[p2.x+1][p2.y+1]==empty) ) return DL;
		else return impossible;
	}
	else if ( (p1.x==p2.x-1) && (p1.y==p2.y-1) ) //Les pions sont en diagonales droites ( de haut en bas ).
	{
		if ((T[p2.x+1][p2.y+1]==empty) || ((((player==player1) && (T[p2.x+1][p2.y+1]==pion2))||((player==player2) && (T[p2.x+1][p2.y+1]==pion1))) && ((T[p2.x+2][p2.y+2]==empty) || (T[p2.x+2][p2.y+2]==gutter))) ) return DR;
		else return impossible;
	}
	else return impossible;
}

//Cas 3 pions. (On considère que p1 est forcément le premier pion cliqué et p2 et p3 dans sa continuité directe).
POSSIBLE move_possible_3( COORD p1, COORD p2, COORD p3, MOVEMENT mov,CASE T[11][21],PLAYER player)
{
	int V;
	V = check_pion_selected_3( p1, p2, p3,T,player);
	//Si l'entier T est à 0, alors tous les pions sélectionnés appartiennent au bon joueur, on peut donc vérifier si le déplacement est autorisé.
	if (V==0)
	{
		switch(mov)
		{
			case left : return move_possible_left_3( p1, p2, p3,T,player); 
				break;
			case right : return move_possible_right_3( p1, p2, p3,T,player); 
				break;
			case up_left : return move_possible_up_left_3( p1, p2, p3,T,player); 	
				break;
			case up_right : return move_possible_up_right_3( p1, p2, p3,T,player); 
				break;
			case down_left : return move_possible_down_left_3( p1, p2, p3,T,player); 
				break;
			case down_right : return move_possible_down_right_3( p1, p2, p3,T,player); 
				break;
			default : return impossible;
				break;
		}
	}
}

int check_pion_selected_3( COORD p1, COORD p2, COORD p3,CASE T[11][21],PLAYER player)
{
	if ( (player==player1) && (T[p1.x][p1.y]==pion1) && (T[p2.x][p2.y]==pion1) && (T[p3.x][p3.y]==pion1) ) return 0;
	else if ((player==player2) && (T[p1.x][p1.y]==pion2) && (T[p2.x][p2.y]==pion2) && (T[p3.x][p3.y]==pion2) ) return 0;
	else return 1;
}

POSSIBLE move_possible_left_3( COORD p1, COORD p2, COORD p3,CASE T[11][21],PLAYER player)
{
	if ((p1.x==p2.x) && (p1.x==p3.x)) //Les pions sont sur la même lignes, on verrifie donc s'il y a un sumito ou si la case à gauche est vide.
	{
		if ((T[p1.x][p3.y-2]==empty) || ((((player==player1) && (T[p1.x][p3.y-2]==pion2))||((player==player2) && (T[p1.x][p3.y-2]==pion1))) && ((T[p1.x][p3.y-4]==empty) || (T[p1.x][p3.y-4]==gutter))) || ((((player==player1) && (T[p1.x][p3.y-2]==pion2) && (T[p1.x][p3.y-4]==pion2))||((player==player2) && (T[p1.x][p3.y-2]==pion1) && (T[p1.x][p3.y-4]==pion1))) && ((T[p1.x][p3.y-6]==empty) || (T[p1.x][p3.y-6]==gutter)))) return line;
		else return impossible;
	}
	else if (( (p1.x==p2.x-1) && (p1.y==p2.y+1) && (p1.x==p3.x-2) && (p1.y==p3.y+2) ) || ( (p1.x==p2.x+1) && (p1.y==p2.y-1) && (p1.x==p3.x+2) && (p1.y==p3.y-2) )) //Les pions sont en diagonales gauches, on verrifie donc que les 3 cases à gauche sont vides.
	{
		if ((T[p1.x][p1.y-2]==empty) && (T[p2.x][p2.y-2]==empty) && (T[p3.x][p3.y-2]==empty)) return DL;
		else return impossible;
	}
	else if (( (p1.x==p2.x+1) && (p1.y==p2.y+1) && (p1.x==p3.x+2) && (p1.y==p3.y+2)) || ((p1.x==p2.x-1) && (p1.y==p2.y-1) && (p1.x==p3.x-2) && (p1.y==p3.y-2) )) //Les pions sont en diagonales droites, on verrifie donc que les 3 cases à gauche sont vides.
	{
		if ((T[p1.x][p1.y-2]==empty) && (T[p2.x][p2.y-2]==empty) && (T[p3.x][p3.y-2]==empty)) return DR;
		else return impossible;
	}
	else return impossible;
}

POSSIBLE move_possible_right_3( COORD p1, COORD p2, COORD p3,CASE T[11][21],PLAYER player)
{
	if ((p1.x==p2.x) && (p1.x==p3.x)) //Les pions sont sur la même lignes, on verrifie donc s'il y a un sumito ou si la case à gauche est vide.
	{
		if ((T[p1.x][p3.y+2]==empty) || ((((player==player1) && (T[p1.x][p3.y+2]==pion2))||((player==player2) && (T[p1.x][p3.y+2]==pion1))) && ((T[p1.x][p3.y+4]==empty) || (T[p1.x][p3.y+4]==gutter))) || ((((player==player1) && (T[p1.x][p3.y+2]==pion2) && (T[p1.x][p3.y+4]==pion2))||((player==player2) && (T[p1.x][p3.y+2]==pion1) && (T[p1.x][p3.y+4]==pion1))) && ((T[p1.x][p3.y+6]==empty) || (T[p1.x][p3.y+6]==gutter)))) return line;
		else return impossible;
	}
	else if (( (p1.x==p2.x-1) && (p1.y==p2.y+1) && (p1.x==p3.x-2) && (p1.y==p3.y+2) ) || ( (p1.x==p2.x+1) && (p1.y==p2.y-1) && (p1.x==p3.x+2) && (p1.y==p3.y-2) )) //Les pions sont en diagonales gauches, on verrifie donc que les 3 cases à gauche sont vides.
	{
		if ((T[p1.x][p1.y+2]==empty) && (T[p2.x][p2.y+2]==empty) && (T[p3.x][p3.y+2]==empty)) return DL;
		else return impossible;
	}
	else if (( (p1.x==p2.x+1) && (p1.y==p2.y+1) && (p1.x==p3.x+2) && (p1.y==p3.y+2)) || ((p1.x==p2.x-1) && (p1.y==p2.y-1) && (p1.x==p3.x-2) && (p1.y==p3.y-2) )) //Les pions sont en diagonales droites, on verrifie donc que les 3 cases à gauche sont vides.
	{
		if ((T[p1.x][p1.y+2]==empty) && (T[p2.x][p2.y+2]==empty) && (T[p3.x][p3.y+2]==empty)) return DR;
		else return impossible;
	}
	else return impossible;
}

POSSIBLE move_possible_up_left_3( COORD p1, COORD p2, COORD p3,CASE T[11][21],PLAYER player)
{
	if ((p1.x==p2.x) && (p1.x==p3.x)) //Les pions sont sur la même lignes, on verrifie donc que les 3 cases en haut à gauche sont vides.
	{
		if ((T[p1.x-1][p1.y-1]==empty) && (T[p2.x-1][p2.y-1]==empty) && (T[p3.x-1][p3.y-1]==empty)) return line;
		else return impossible;
	}
	else if (( (p1.x==p2.x-1) && (p1.y==p2.y+1) && (p1.x==p3.x-2) && (p1.y==p3.y+2) ) || ( (p1.x==p2.x+1) && (p1.y==p2.y-1) && (p1.x==p3.x+2) && (p1.y==p3.y-2) )) //Les pions sont en diagonales gauches ( de haut en bas ).
	{
		if ((T[p1.x-1][p1.y-1]==empty) && (T[p2.x-1][p2.y-1]==empty) && (T[p3.x-1][p3.y-1]==empty)) return DL;
		else return impossible;
	}
	else if ((p1.x==p2.x+1) && (p1.y==p2.y+1) && (p1.x==p3.x+2) && (p1.y==p3.y+2)) //Les pions sont en diagonales droites ( de haut en bas ).
	{
		if ((T[p3.x-1][p3.y-1]==empty) || ((((player==player1) && (T[p3.x-1][p3.y-1]==pion2))||((player==player2) && (T[p3.x-1][p3.y-1]==pion1))) && ((T[p3.x-2][p3.y-2]==empty) || (T[p3.x-2][p3.y-2]==gutter))) || ((((player==player1) && (T[p3.x-1][p3.y-1]==pion2) && (T[p3.x-2][p3.y-2]==pion2))||((player==player2) && (T[p3.x-1][p3.y-1]==pion1) && (T[p3.x-2][p3.y-2]==pion1))) && ((T[p3.x-3][p3.y-3]==empty) || (T[p3.x-3][p3.y-3]==gutter)))) return DR;
		else return impossible;
	}
	else return impossible;
}

POSSIBLE move_possible_up_right_3( COORD p1, COORD p2, COORD p3,CASE T[11][21],PLAYER player)
{
	if ((p1.x==p2.x) && (p1.x==p3.x)) //Les pions sont sur la même lignes, on verrifie donc que les 3 cases en haut à droite sont vides.
	{
		if ((T[p1.x-1][p1.y+1]==empty) && (T[p2.x-1][p2.y+1]==empty) && (T[p3.x-1][p3.y+1]==empty)) return line;
		else return impossible;
	}
	else if ( ((p1.x==p2.x+1) && (p1.y==p2.y+1) && (p1.x==p3.x+2) && (p1.y==p3.y+2)) || ((p1.x==p2.x-1) && (p1.y==p2.y-1) && (p1.x==p3.x-2) && (p1.y==p3.y-2)) ) //Les pions sont en diagonales droites ( de haut en bas ).
	{
		if ((T[p1.x-1][p1.y+1]==empty) && (T[p2.x-1][p2.y+1]==empty) && (T[p3.x-1][p3.y+1]==empty)) return DR;
		else return impossible;
	}
	else if ((p1.x==p2.x+1) && (p1.y==p2.y-1) && (p1.x==p3.x+2) && (p1.y==p3.y-2)) //Les pions sont en diagonales gauches ( de haut en bas ).
	{
		if ((T[p3.x-1][p3.y+1]==empty) || ((((player==player1) && (T[p3.x-1][p3.y+1]==pion2))||((player==player2) && (T[p3.x-1][p3.y+1]==pion1))) && ((T[p3.x-2][p3.y+2]==empty) || (T[p3.x-2][p3.y+2]==gutter))) || ((((player==player1) && (T[p3.x-1][p3.y+1]==pion2) && (T[p3.x-2][p3.y+2]==pion2))||((player==player2) && (T[p3.x-1][p3.y+1]==pion1) && (T[p3.x-2][p3.y+2]==pion1))) && ((T[p3.x-3][p3.y+3]==empty) || (T[p3.x-3][p3.y+3]==gutter)))) return DL;
		else return impossible;
	}
	else return impossible;
}

POSSIBLE move_possible_down_left_3( COORD p1, COORD p2, COORD p3,CASE T[11][21],PLAYER player)
{
	if ((p1.x==p2.x) && (p1.x==p3.x)) //Les pions sont sur la même lignes, on verrifie donc que les 3 cases en bas à gauche sont vides.
	{
		if ((T[p1.x+1][p1.y-1]==empty) && (T[p2.x+1][p2.y-1]==empty) && (T[p3.x+1][p3.y-1]==empty)) return line;
		else return impossible;
	}
	else if ( ((p1.x==p2.x+1) && (p1.y==p2.y+1) && (p1.x==p3.x+2) && (p1.y==p3.y+2)) || ((p1.x==p2.x-1) && (p1.y==p2.y-1) && (p1.x==p3.x-2) && (p1.y==p3.y-2)) ) //Les pions sont en diagonales droites ( de haut en bas ).
	{
		if ((T[p1.x+1][p1.y-1]==empty) && (T[p2.x+1][p2.y-1]==empty) && (T[p3.x+1][p3.y-1]==empty)) return DR;
		else return impossible;
	}
	else if ((p1.x==p2.x-1) && (p1.y==p2.y+1) && (p1.x==p3.x-2) && (p1.y==p3.y+2)) //Les pions sont en diagonales gauches ( de haut en bas ).
	{
		if ((T[p3.x+1][p3.y-1]==empty) || ((((player==player1) && (T[p3.x+1][p3.y-1]==pion2))||((player==player2) && (T[p3.x+1][p3.y-1]==pion1))) && ((T[p3.x+2][p3.y-2]==empty) || (T[p3.x+2][p3.y-2]==gutter))) || ((((player==player1) && (T[p3.x+1][p3.y-1]==pion2) && (T[p3.x+2][p3.y-2]==pion2))||((player==player2) && (T[p3.x+1][p3.y-1]==pion1) && (T[p3.x+2][p3.y-2]==pion1))) && ((T[p3.x+3][p3.y-3]==empty) || (T[p3.x+3][p3.y-3]==gutter)))) return DL;
		else return impossible;
	}
	else return impossible;
}

POSSIBLE move_possible_down_right_3( COORD p1, COORD p2, COORD p3,CASE T[11][21],PLAYER player)
{
	if ((p1.x==p2.x) && (p1.x==p3.x)) //Les pions sont sur la même lignes, on verrifie donc que les 3 cases en haut à gauche sont vides.
	{
		if ((T[p1.x+1][p1.y+1]==empty) && (T[p2.x+1][p2.y+1]==empty) && (T[p3.x+1][p3.y+1]==empty)) return line;
		else return impossible;
	}
	else if (( (p1.x==p2.x-1) && (p1.y==p2.y+1) && (p1.x==p3.x-2) && (p1.y==p3.y+2) ) || ( (p1.x==p2.x+1) && (p1.y==p2.y-1) && (p1.x==p3.x+2) && (p1.y==p3.y-2) )) //Les pions sont en diagonales gauches ( de haut en bas ).
	{
		if ((T[p1.x+1][p1.y+1]==empty) && (T[p2.x+1][p2.y+1]==empty) && (T[p3.x+1][p3.y+1]==empty)) return DL;
		else return impossible;
	}
	else if ((p1.x==p2.x-1) && (p1.y==p2.y-1) && (p1.x==p3.x-2) && (p1.y==p3.y-2)) //Les pions sont en diagonales droites ( de haut en bas ).
	{
		if ((T[p3.x+1][p3.y+1]==empty) || ((((player==player1) && (T[p3.x+1][p3.y+1]==pion2))||((player==player2) && (T[p3.x+1][p3.y+1]==pion1))) && ((T[p3.x+2][p3.y+2]==empty) || (T[p3.x+2][p3.y+2]==gutter))) || ((((player==player1) && (T[p3.x+1][p3.y+1]==pion2) && (T[p3.x+2][p3.y+2]==pion2))||((player==player2) && (T[p3.x+1][p3.y+1]==pion1) && (T[p3.x+2][p3.y+2]==pion1))) && ((T[p3.x+3][p3.y+3]==empty) || (T[p3.x+3][p3.y+3]==gutter)))) return DR;
		else return impossible;
	}
	else return impossible;
}



//Les fonctions qui suivent permettent de faire le déplacement (mais elles ne vérifient pas si le mouvement est possible)
//Les fonctions prennent en argument les coordonnées de la case a deplacer 
void move( COORD p1, COORD p2, COORD p3, MOVEMENT mov, POSSIBLE alignment,CASE T[11][21])
{
	int nb;
	nb = number_pions(p1, p2, p3);
	switch(nb)
	{
		case 1 : move_1( p1, mov, alignment,T);
			break;
		case 2 : move_2( p1, p2, mov, alignment,T);
			break;
		case 3 : move_3( p1, p2, p3, mov, alignment,T);
			break;
		default : break;
	}
	swap_player();
}

void affiche(CASE T[11][21])
{
	int l,c;
	for (l=0;l<=10;l++)
	{
		for (c=0;c<=20;c++)
		{
			if (T[l][c]==empty) printf(".");
			else if (T[l][c]==pion1) printf("1");
			else if(T[l][c]==pion2) printf("2");
			else if(T[l][c]==gutter) printf(" ");
			else if(T[l][c]==prohibited) printf(" ");
		}
		printf("\n");
	}
}

//Mouvements 1 pion
void move_1( COORD p1, MOVEMENT mov, POSSIBLE alignment,CASE T[11][21])
{
	switch(mov)
	{
		case left : move_left_1( p1,T); 
			break;
		case right : move_right_1( p1,T); 
			break;
		case up_left : move_up_left_1( p1,T); 	
			break;
		case up_right : move_up_right_1( p1,T); 
			break;
		case down_left : move_down_left_1( p1,T); 
			break;
		case down_right : move_down_right_1( p1,T); 
			break;
		default : break;
	}
}

void move_left_1 (COORD p1,CASE T[11][21]) 
{
	T[p1.x][p1.y-2]=T[p1.x][p1.y];
	T[p1.x][p1.y]=0;
}

void move_right_1 (COORD p1,CASE T[11][21])
{
	T[p1.x][p1.y+2]=T[p1.x][p1.y];
	T[p1.x][p1.y]=0;
}

void move_up_left_1 (COORD p1,CASE T[11][21])
{
	T[p1.x-1][p1.y-1]=T[p1.x][p1.y];
	T[p1.x][p1.y]=0;
}

void move_up_right_1 (COORD p1,CASE T[11][21])	
{			      
	T[p1.x-1][p1.y+1]=T[p1.x][p1.y];
	T[p1.x][p1.y]=0;
}

void move_down_left_1 (COORD p1,CASE T[11][21])
{
	T[p1.x+1][p1.y-1]=T[p1.x][p1.y];
	T[p1.x][p1.y]=0;
}

void move_down_right_1 (COORD p1,CASE T[11][21])
{
	T[p1.x+1][p1.y+1]=T[p1.x][p1.y];
	T[p1.x][p1.y]=0;
}

//Mouvement 2 pions
//On suppose que les pions peuvent être selectionnés dans n'importe quel ordre
void move_2( COORD p1, COORD p2, MOVEMENT mov, POSSIBLE alignment,CASE T[11][21])
{
	switch(mov)
	{
		case left : move_left_2( p1, p2, alignment,T); 
			break;
		case right : move_right_2( p1, p2, alignment,T); 
			break;
		case up_left : move_up_left_2( p1, p2, alignment,T); 	
			break;
		case up_right : move_up_right_2( p1, p2, alignment,T); 
			break;
		case down_left : move_down_left_2( p1, p2, alignment,T); 
			break;
		case down_right : move_down_right_2( p1, p2, alignment,T); 
			break;
		default : break;
	}
}

void move_left_2 (COORD p1,COORD p2,POSSIBLE alignment,CASE T[11][21])
{
	int x,y;
	if (alignment != line)
	{
		T[p1.x][p1.y-2]=T[p1.x][p1.y];
		T[p1.x][p1.y]=empty;
		T[p2.x][p2.y-2]=T[p2.x][p2.y];
		T[p2.x][p2.y]=empty;
	}
	else
	{
		if (p2.y < p1.y)
		{
			x=p1.x; 	y=p1.y;
			p1.x=p2.x;  p1.y=p2.y;
			p2.x=x;     p2.y=y;
		}
		if (T[p1.x][p1.y-2] != empty)
		{
			if (T[p1.x][p1.y-4] == empty)
			{
				T[p1.x][p1.y-4]=T[p1.x][p1.y-2];
			}
			else
			{
				//score++;
			}
		}
		T[p1.x][p1.y-2]=T[p2.x][p2.y];
		T[p2.x][p2.y]=empty;
	}
}

void move_right_2 (COORD p1,COORD p2,POSSIBLE alignment,CASE T[11][21])
{	
	int x,y;
	if (alignment != line)
	{
		T[p1.x][p1.y+2]=T[p1.x][p1.y];
		T[p1.x][p1.y]=empty;
		T[p2.x][p2.y+2]=T[p2.x][p2.y];
		T[p2.x][p2.y]=empty;
	}
	else
	{
		if (p2.y < p1.y)
		{
			x=p1.x; 	y=p1.y;
			p1.x=p2.x;  p1.y=p2.y;
			p2.x=x;     p2.y=y;
		}
		if (T[p2.x][p2.y+2] != empty)
		{
			if (T[p2.x][p2.y+4] == empty)
			{
				T[p2.x][p2.y+4]=T[p2.x][p2.y+2];
			}
			else
			{
				//score++;
			}
		}
		T[p2.x][p2.y+2]=T[p1.x][p1.y];
		T[p1.x][p1.y]=empty;
	}
}

void move_up_left_2 (COORD p1, COORD p2,POSSIBLE alignment,CASE T[11][21])
{
	int x,y;
	if (alignment==line || alignment==DL) //Cas où les pions sont sur la même ligne, ou deplacement simple (pas sumito)
	{
		T[p1.x-1][p1.y-1]=T[p1.x][p1.y];
		T[p1.x][p1.y]=empty;
		T[p2.x-1][p2.y-1]=T[p2.x][p2.y];
		T[p2.x][p2.y]=empty;
	}
	else //Cas diagonales (possible sumito)
	{
		if (p2.x < p1.x)
		{
			x=p1.x; 	y=p1.y;
			p1.x=p2.x;  p1.y=p2.y;
			p2.x=x;     p2.y=y;
		}
		if (T[p1.x-1][p1.y-1] != empty)
		{
			if (T[p1.x-2][p1.y-2] == empty)
			{
				T[p1.x-2][p1.y-2]=T[p1.x-1][p1.y-1];
			}
			else
			{
				//score++;
			}
		}
		T[p1.x-1][p1.y-1]=T[p2.x][p2.y];
		T[p2.x][p2.y]=empty;
	}	
}

void move_up_right_2 (COORD p1, COORD p2,POSSIBLE alignment,CASE T[11][21])
{
	int x,y;
	if (alignment==line || alignment==DR) 
	//Cas où on les pions se trouvent sur la même ligne, ou en diagonale (pas sumito)
	{
		T[p1.x-1][p1.y+1]=T[p1.x][p1.y];
		T[p1.x][p1.y]=empty;
		T[p2.x-1][p2.y+1]=T[p2.x][p2.y];
		T[p2.x][p2.y]=empty;
	}
	else //Cas diagonales (possible sumito)
	{
		if (p2.y < p1.y)
		{
			x=p1.x; 	y=p1.y;
			p1.x=p2.x;  p1.y=p2.y;
			p2.x=x;     p2.y=y;
		}
		if (T[p2.x-1][p2.y+1] != empty)
		{
			if (T[p2.x-2][p2.y+2] == empty)
			{
				T[p2.x-2][p2.y+2]=T[p2.x-1][p2.y+1];
			}
			else
			{
				//score++;
			}
		}
		T[p2.x-1][p2.y+1]=T[p1.x][p1.y];
		T[p1.x][p1.y]=empty;
	}	
}

void move_down_left_2 (COORD p1, COORD p2, POSSIBLE alignment,CASE T[11][21])
{
	int x,y;
	if (alignment==line || alignment==DR) //Cas où on les pions se trouvent sur la même ligne,ou en diagonale (pas sumito)
	{
		T[p1.x+1][p1.y-1]=T[p1.x][p1.y];
		T[p1.x][p1.y]=empty;
		T[p2.x+1][p2.y-1]=T[p2.x][p2.y];
		T[p2.x][p2.y]=empty;
	}
	else //Cas diagonales (possible sumito)
	{
		if (p1.x < p2.x)
		{
			x=p1.x; 	y=p1.y;
			p1.x=p2.x;  p1.y=p2.y;
			p2.x=x;     p2.y=y;
		}
		if (T[p1.x+1][p1.y-1] != empty)
		{
			if (T[p1.x+2][p1.y-2] == empty)
			{
				T[p1.x+2][p1.y-2]=T[p1.x+1][p1.y-1];
			}
			else
			{
				//score++;
			}
		}
		T[p1.x+1][p1.y-1]=T[p2.x][p2.y];
		T[p2.x][p2.y]=empty;
	}	
}

void move_down_right_2 (COORD p1, COORD p2,POSSIBLE alignment,CASE T[11][21])
{
	int x,y;
	if (alignment==line || alignment==DL) 
	//Cas où on les pions se trouvent sur la même ligne, ou en diagonale (pas sumito)
	{
		T[p1.x+1][p1.y+1]=T[p1.x][p1.y];
		T[p1.x][p1.y]=empty;
		T[p2.x+1][p2.y+1]=T[p2.x][p2.y];
		T[p2.x][p2.y]=empty;
	}
	else //Cas diagonales (possible sumito)
	{
		if (p2.y < p1.y)
		{
			x=p1.x; 	y=p1.y;
			p1.x=p2.x;  p1.y=p2.y;
			p2.x=x;     p2.y=y;
		}
		if (T[p2.x+1][p2.y+1] != empty)
		{
			if (T[p2.x+2][p2.y+2] == empty)
			{
				T[p2.x+2][p2.y+2]=T[p2.x+1][p2.y+1];
			}
			else
			{
				//score++;
			}
		}
		T[p2.x+1][p2.y+1]=T[p1.x][p1.y];
		T[p1.x][p1.y]=empty;
	}	
}

//Mouvement 3 pions
//On suppose que les points p1 sont dans l'ordre dans lequel on veut les déplacer
void move_3( COORD p1, COORD p2, COORD p3, MOVEMENT mov, POSSIBLE alignment,CASE T[11][21])
{
	switch(mov)
	{
		case left : move_left_3( p1, p2, p3, alignment,T); 
			break;
		case right : move_right_3( p1, p2, p3, alignment,T); 
			break;
		case up_left : move_up_left_3( p1, p2, p3, alignment,T); 	
			break;
		case up_right : move_up_right_3( p1, p2, p3, alignment,T); 
			break;
		case down_left : move_down_left_3( p1, p2, p3, alignment,T); 
			break;
		case down_right : move_down_right_3( p1, p2, p3, alignment,T); 
			break;
		default : break;
	}
}

void move_left_3 (COORD p1,COORD p2,COORD p3,POSSIBLE alignment,CASE T[11][21])
{
	int x,y;
	if (alignment != line)
	{
		T[p1.x][p1.y-2]=T[p1.x][p1.y];	T[p1.x][p1.y]=empty;
		T[p2.x][p2.y-2]=T[p2.x][p2.y];	T[p2.x][p2.y]=empty;
		T[p3.x][p3.y-2]=T[p3.x][p3.y];	T[p3.x][p3.y]=empty;
	}
	else
	{
		if (T[p3.x][p3.y-2] != empty)
		{
			if ((T[p3.x][p3.y-4] != empty) && (T[p3.x][p3.y-6] == gutter))
			{
				//score++;
			}
			else if (T[p3.x][p3.y-4] == empty)
			{
				T[p3.x][p3.y-4]=T[p3.x][p3.y-2];
			}
			else
			{
				T[p3.x][p3.y-6]=T[p3.x][p3.y-2];
			}
		}
		T[p3.x][p3.y-2]=T[p1.x][p1.y];
		T[p1.x][p1.y]=empty;
	}
}

void move_right_3 (COORD p1,COORD p2,COORD p3,POSSIBLE alignment,CASE T[11][21])
{
	int x,y;
	if (alignment != line)
	{
		T[p1.x][p1.y+2]=T[p1.x][p1.y];	T[p1.x][p1.y]=empty;
		T[p2.x][p2.y+2]=T[p2.x][p2.y];	T[p2.x][p2.y]=empty;
		T[p3.x][p3.y+2]=T[p3.x][p3.y];	T[p3.x][p3.y]=empty;
	}
	else
	{
		if (T[p3.x][p3.y+2] != empty)
		{
			if ((T[p3.x][p3.y+4] != empty) && (T[p3.x][p3.y+6] == gutter))
			{
				//score++;
			}
			else if (T[p3.x][p3.y+4] == empty)
			{
				T[p3.x][p3.y+4]=T[p3.x][p3.y+2];
			}
			else
			{
				T[p3.x][p3.y+6]=T[p3.x][p3.y+2];
			}
		}
		T[p3.x][p3.y+2]=T[p1.x][p1.y];
		T[p1.x][p1.y]=empty;
	}
}

void move_up_left_3 (COORD p1, COORD p2,COORD p3,POSSIBLE alignment,CASE T[11][21])
{
	int x,y;
	if (alignment==line || alignment==DL) //Cas où les pions sont sur la même ligne, ou deplacement simple (pas sumito)
	{
		T[p1.x-1][p1.y-1]=T[p1.x][p1.y];	T[p1.x][p1.y]=empty;
		T[p2.x-1][p2.y-1]=T[p2.x][p2.y];	T[p2.x][p2.y]=empty;
		T[p3.x-1][p3.y-1]=T[p3.x][p3.y];	T[p3.x][p3.y]=empty;
	}
	else //Cas diagonales (possible sumito)
	{
		if (T[p3.x-1][p3.y-1] != empty)
		{
			if ((T[p3.x-2][p3.y-2] != empty) && (T[p3.x-3][p3.y-3] == gutter))
			{
				//score++;
			}
			else if (T[p3.x-2][p3.y-2] == empty)
			{
				T[p3.x-2][p3.y-2]=T[p3.x-1][p3.y-1];
			}
			else
			{
				T[p3.x-3][p3.y-3]=T[p3.x-1][p3.y-1];
			}
		}
		T[p3.x-1][p3.y-1]=T[p1.x][p1.y];
		T[p1.x][p1.y]=empty;
	}
}

void move_up_right_3 (COORD p1, COORD p2,COORD p3,POSSIBLE alignment,CASE T[11][21])
{
	int x,y;
	if (alignment==line || alignment==DR) //Cas où les pions sont sur la même ligne, ou deplacement simple (pas sumito)
	{
		T[p1.x-1][p1.y+1]=T[p1.x][p1.y];	T[p1.x][p1.y]=empty;
		T[p2.x-1][p2.y+1]=T[p2.x][p2.y];	T[p2.x][p2.y]=empty;
		T[p3.x-1][p3.y+1]=T[p3.x][p3.y];	T[p3.x][p3.y]=empty;
	}
	else //Cas diagonales (possible sumito)
	{
		if (T[p3.x-1][p3.y+1] != empty)
		{
			if ((T[p3.x-2][p3.y+2] != empty) && (T[p3.x-3][p3.y+3] == gutter))
			{
				//score++;
			}
			else if (T[p3.x-2][p3.y+2] == empty)
			{
				T[p3.x-2][p3.y+2]=T[p3.x-1][p3.y+1];
			}
			else
			{
				T[p3.x-3][p3.y+3]=T[p3.x-1][p3.y+1];
			}
		}
		T[p3.x-1][p3.y+1]=T[p1.x][p1.y];
		T[p1.x][p1.y]=empty;
	}
}

void move_down_left_3 (COORD p1, COORD p2,COORD p3,POSSIBLE alignment,CASE T[11][21])
{
	int x,y;
	if (alignment==line || alignment==DR) //Cas où les pions sont sur la même ligne, ou deplacement simple (pas sumito)
	{
		T[p1.x+1][p1.y-1]=T[p1.x][p1.y];	T[p1.x][p1.y]=empty;
		T[p2.x+1][p2.y-1]=T[p2.x][p2.y];	T[p2.x][p2.y]=empty;
		T[p3.x+1][p3.y-1]=T[p3.x][p3.y];	T[p3.x][p3.y]=empty;
	}
	else //Cas diagonales (possible sumito)
	{
		if (T[p3.x+1][p3.y-1] != empty)
		{
			if ((T[p3.x+2][p3.y-2] != empty) && (T[p3.x+3][p3.y-3] == gutter))
			{
				//score++;
			}
			else if (T[p3.x+2][p3.y-2] == empty)
			{
				T[p3.x+2][p3.y-2]=T[p3.x+1][p3.y-1];
			}
			else
			{
				T[p3.x+3][p3.y-3]=T[p3.x+1][p3.y-1];
			}
		}
		T[p3.x+1][p3.y-1]=T[p1.x][p1.y];
		T[p1.x][p1.y]=empty;
	}
}

void move_down_right_3 (COORD p1, COORD p2,COORD p3,POSSIBLE alignment,CASE T[11][21])
{
	int x,y;
	if (alignment==line || alignment==DL) //Cas où les pions sont sur la même ligne, ou deplacement simple (pas sumito)
	{
		T[p1.x+1][p1.y+1]=T[p1.x][p1.y];	T[p1.x][p1.y]=empty;
		T[p2.x+1][p2.y+1]=T[p2.x][p2.y];	T[p2.x][p2.y]=empty;
		T[p3.x+1][p3.y+1]=T[p3.x][p3.y];	T[p3.x][p3.y]=empty;
	}
	else //Cas diagonales (possible sumito)
	{
		if (T[p3.x+1][p3.y+1] != empty)
		{
			if ((T[p3.x+2][p3.y+2] != empty) && (T[p3.x+3][p3.y+3] == gutter))
			{
				//score++;
			}
			else if (T[p3.x+2][p3.y+2] == empty)
			{
				T[p3.x+2][p3.y+2]=T[p3.x+1][p3.y+1];
			}
			else
			{
				T[p3.x+3][p3.y+3]=T[p3.x+1][p3.y+1];
			}
		}
		T[p3.x+1][p3.y+1]=T[p1.x][p1.y];
		T[p1.x][p1.y]=empty;
	}
}


//Fonctions pour l'initialisation du plateau de départ 
//Permet de copier le tableau avec les positions de départ choisi dans le tableau de jeu
void copy_tab(CASE T_reference[11][21], CASE T_variant[11][21])
{
	int l,c;
	for (l=0;l<11;l++)
	{
		for (c=0;c<21;c++)
		{
			T_reference[l][c]=T_variant[l][c];
		}
	}
}

void insert_pion(CASE p)
{
	int r,l,c,i,compt;
	int cases_vides=61;
	int nb_pions=14;
	while (nb_pions >0)
	{
		compt=0;
		r=(rand()%cases_vides);
		for (l=0;l<11;l++)
		{
			for (c=0;c<21;c++)
			{
				if (T_aleatoire[l][c]==empty)
				{
					if (compt==r+1)
					{
						T_aleatoire[l][c]=p;
						cases_vides--;
						nb_pions--;
					}
					compt++;
				}
			}
		}	
	}
}		

void aleatoire_tab()
{
	insert_pion(pion1);
	insert_pion(pion2);
}

//Permet d'appeler le tableau de position de départ	souhaité
void init_tab(START_POSITION pos)
{
	switch (pos)
	{
		case standard: copy_tab(T_reference,T_standard);
						 break;
		case daisy: copy_tab(T_reference,T_daisy);
						 break;
		case domination: copy_tab(T_reference,T_domination);
						 break;
		case face_to_face: copy_tab(T_reference,T_face_to_face);
						 break;
		case snake: copy_tab(T_reference,T_snake);
						 break;
		case alliance: copy_tab(T_reference,T_alliance);
						 break;
		case labyrinth: copy_tab(T_reference,T_labyrinth);
						 break;
		case aleatoire: aleatoire_tab();
					 copy_tab(T_reference,T_aleatoire);
					 break;
		default: break;			 
	}
}

//Condition de victoire
int is_victory()
{
	if( (score1==condition_pion) || (score2==condition_pion) || ((condition_coup<=0) && (condition_coup!=-1)) ) //la partie est terminé
		return 1;
	else 
		return 0;
}

//////////// IA /////////////
int number_pions(COORD p1, COORD p2, COORD p3)
{
	if((p3.x==0) && (p2.x==0)) return 1;
	else if(p3.x==0) return 2;
	else return 3;
}

int value_board(CASE T[11][21],PLAYER player)
{
	int l,c,of,def;
	int val=0;
	if (player==player1)
	{
		of=pion1;
		def=pion2;
	}
	else if (player==player2)
	{
		of=pion2;
		def=pion1;
	}
	for (l=0;l<11;l++)
	{
		for (c=0;c<21;c++)
		{
			if (T[l][c]==of)
			{
				val += V[l][c];
				val += 100;
			}
			else if (T[l][c]==def)
			{
				val -= V[l][c];
				val -=100;
			}
		}
	}
	return val;
}

lc add_list(lc liste,COORD pos1,COORD pos2,COORD pos3,CASE T[11][21])
{
	DEP_IA_POSSIBLE * new_element= malloc(1*sizeof(DEP_IA_POSSIBLE));
	
	new_element->p1.x=pos1.x;
	new_element->p1.y=pos1.y;
	new_element->p2.x=pos2.x;
	new_element->p2.y=pos2.y;
	new_element->p3.x=pos3.x;
	new_element->p3.y=pos3.y;
	
	new_element->suivant=liste;
	return new_element;
}

lc pions_together(lc liste,CASE pawn,int l,int c,CASE T[11][21])
{	
	COORD pos1,pos2,pos3; 
	pos1.x=l;	pos1.y=c;
	pos2.x=0;	pos2.y=0;
	pos3.x=0;	pos3.y=0;
	liste=add_list(liste,pos1,pos2,pos3,T);	
	if (T[l][c+2]==pawn) //CAS EN LIGNE
	{
		pos2.x=l;	pos2.y=c+2;
		liste=add_list(liste,pos1,pos2,pos3,T);
		if (T[l][c+4]==pawn)
		{
			pos3.x=l;	pos3.y=c+4;
			liste=add_list(liste,pos1,pos2,pos3,T);
		}	
	}
	pos2.x=0;	pos2.y=0;
	pos3.x=0;	pos3.y=0;
	if (T[l+1][c-1]==pawn) //CAS DL
	{
		pos2.x=l+1;	pos2.y=c-1;
		liste=add_list(liste,pos1,pos2,pos3,T);
		if (T[l+2][c-2]==pawn)
		{
			pos3.x=l+2;	pos3.y=c-2;
			liste=add_list(liste,pos1,pos2,pos3,T);
		}				
	}
	pos2.x=0;	pos2.y=0;
	pos3.x=0;	pos3.y=0;
	if (T[l+1][c+1]==pawn) //CAS DR
	{
		pos2.x=l+1;	pos2.y=c+1;
		liste=add_list(liste,pos1,pos2,pos3,T);
		if (T[l+2][c+2]==pawn)
		{
			pos3.x=l+2;	pos3.y=c+2;
			liste=add_list(liste,pos1,pos2,pos3,T);
		}				
	}
	return liste;
}

lc pions_together_inverse(lc liste,CASE pawn,int l,int c,CASE T[11][21])
{	
	COORD pos1,pos2,pos3; 
	pos1.x=l;	pos1.y=c;
	pos2.x=0;	pos2.y=0;
	pos3.x=0;	pos3.y=0;
	liste=add_list(liste,pos1,pos2,pos3,T);	
	if (T[l][c-2]==pawn) //CAS EN LIGNE
	{
		pos2.x=l;	pos2.y=c-2;
		liste=add_list(liste,pos1,pos2,pos3,T);
		if (T[l][c-4]==pawn)
		{
			pos3.x=l;	pos3.y=c-4;
			liste=add_list(liste,pos1,pos2,pos3,T);
		}	
	}
	pos2.x=0;	pos2.y=0;
	pos3.x=0;	pos3.y=0;
	if (T[l-1][c+1]==pawn) //CAS DL
	{
		pos2.x=l-1;	pos2.y=c+1;
		liste=add_list(liste,pos1,pos2,pos3,T);
		if (T[l-2][c+2]==pawn)
		{
			pos3.x=l-2;	pos3.y=c+2;
			liste=add_list(liste,pos1,pos2,pos3,T);
		}				
	}
	pos2.x=0;	pos2.y=0;
	pos3.x=0;	pos3.y=0;
	if (T[l-1][c-1]==pawn) //CAS DR
	{
		pos2.x=l-1;	pos2.y=c-1;
		liste=add_list(liste,pos1,pos2,pos3,T);
		if (T[l-2][c-2]==pawn)
		{
			pos3.x=l-2;	pos3.y=c-2;
			liste=add_list(liste,pos1,pos2,pos3,T);
		}				
	}
	return liste;
}

lc gather_pions_possible(CASE T[11][21],PLAYER player)
{
	lc liste=NULL;
	int l,c;
	COORD pos1,pos2,pos3;
	CASE pawn;
	if (player==player1)
		pawn=pion1;
	else
		pawn=pion2;
		
	for (l=0;l<11;l++)
	{
		for (c=0;c<21;c++)
		{
			if (T[l][c]==pawn)
				liste=pions_together(liste,pawn,l,c,T);
				liste=pions_together_inverse(liste,pawn,l,c,T);
		}
	}
	return liste;
}

void affichage_lc(lc liste)
{
	DEP_IA_POSSIBLE * courant=liste;
	while (courant!= NULL)
	{
		printf("(%d,%d) ",courant->p1.x,courant->p1.y);
		printf("(%d,%d) ",courant->p2.x,courant->p2.y);
		printf("(%d,%d)\n",courant->p3.x,courant->p3.y);
		courant=courant->suivant;
	}
}		

int maximum(int a, int b)
{
	if(a>b)
		return a;
	else
		return b;
}	

int minimum(int a, int b)
{
	if(a<b)
		return a;
	else 
		return b;
}

int Min(CASE T_bis[11][21], int depth, int alpha, int beta, PLAYER player_bis)
{
	int tmp, nb, i;
	int Min_val= 10000;
	POSSIBLE result;
	MOVEMENT dep, result_dep;
	CASE T_tmp[11][21];
	PLAYER opponent;
	lc list_pions;	
	
	if( player_bis==player1) opponent==player2;
	else opponent==player1;
	
	if((depth==0) || (is_victory()==1))
		return value_board( T_bis, opponent);
	
	copy_tab(T_tmp,T_bis);
	list_pions=gather_pions_possible(T_bis,player_bis);
	DEP_IA_POSSIBLE * courant=list_pions;
	
	while(courant!=NULL)
	{
		for(i=0;i<6;i++)
		{
			switch(i)
			{
				case 0 : result = move_possible( courant->p1, courant->p2, courant->p3, left, T_bis,player_bis);
					dep=left;
					break;
				case 1 : result = move_possible( courant->p1, courant->p2, courant->p3, right, T_bis,player_bis);
					dep=right;
					break;
				case 2 : result = move_possible( courant->p1, courant->p2, courant->p3, up_left, T_bis,player_bis);
					dep=up_left;
					break;
				case 3 : result = move_possible( courant->p1, courant->p2, courant->p3, up_right, T_bis,player_bis);
					dep=up_right;
					break;
				case 4 : result = move_possible( courant->p1, courant->p2, courant->p3, down_left, T_bis,player_bis);
					dep=down_left;
					break;
				case 5 : result = move_possible( courant->p1, courant->p2, courant->p3, down_right, T_bis,player_bis);
					dep=down_right;
					break;
				default : break;
			}
			if(result != impossible) 
				move( courant->p1, courant->p2, courant->p3, dep,result,T_bis);	
			else
				continue; // On passe à l'itération suivante du if
					
			Min_val=minimum(Min_val,Max(T_bis, depth-1, alpha, beta, opponent));
			if(Min_val<=alpha) return Min_val;
			beta=minimum(beta,Min_val);
			copy_tab(T_bis,T_tmp); //Annulation du coup effectué.
		}
		courant=courant->suivant;
	}
	return Min_val;
}	
int Max(CASE T_bis[11][21], int depth, int alpha, int beta, PLAYER player_bis)
{
	int tmp, nb, i;
	int Max_val= -10000;
	POSSIBLE result;
	MOVEMENT dep, result_dep;
	CASE T_tmp[11][21];
	PLAYER opponent;
	lc list_pions;
	
	if( player_bis==player1) opponent==player2;
	else opponent==player1;
	
	if((depth==0) || (is_victory()==1))
		return value_board( T_bis, player_bis);
	
	copy_tab(T_tmp,T_bis);
	
	list_pions=gather_pions_possible(T_bis,player_bis);
	DEP_IA_POSSIBLE * courant=list_pions;
	
	while(courant!=NULL)
	{
		for(i=0;i<6;i++)
		{
			switch(i)
			{
				case 0 : result = move_possible( courant->p1, courant->p2, courant->p3, left, T_bis,player_bis);
					dep=left;
					break;
				case 1 : result = move_possible( courant->p1, courant->p2, courant->p3, right, T_bis,player_bis);
					dep=right;
					break;
				case 2 : result = move_possible( courant->p1, courant->p2, courant->p3, up_left, T_bis,player_bis);
					dep=up_left;
					break;
				case 3 : result = move_possible( courant->p1, courant->p2, courant->p3, up_right, T_bis,player_bis);
					dep=up_right;
					break;
				case 4 : result = move_possible( courant->p1, courant->p2, courant->p3, down_left, T_bis,player_bis);
					dep=down_left;
					break;
				case 5 : result = move_possible( courant->p1, courant->p2, courant->p3, down_right, T_bis,player_bis);
					dep=down_right;
					break;
				default : break;
			}
			if(result != impossible) 
				move( courant->p1, courant->p2, courant->p3, dep,result,T_bis);	
			else
				continue; // On passe à l'itération suivante du if
					
			Max_val=maximum(Max_val,Min(T_bis, depth-1, alpha, beta, opponent));
			if(Max_val>=beta) return Max_val;
			alpha=maximum(alpha,Max_val);
			copy_tab(T_bis,T_tmp); //Annulation du coup effectué.
		}
		courant=courant->suivant;
	}
	return Max_val;
}


MOVEMENT alpha_beta(CASE T_bis[11][21], int depth, int alpha, int beta, PLAYER player_bis, COORD* p1, COORD* p2, COORD* p3)
{
	int tmp, nb, i;
	int Max_val=-10000;
	POSSIBLE result;
	MOVEMENT dep, result_dep;
	CASE T_tmp[11][21];
	PLAYER opponent;
	lc list_pions;

	list_pions=gather_pions_possible(T_bis,player_bis);
	DEP_IA_POSSIBLE * courant=list_pions;
	
	copy_tab(T_tmp,T_bis); // Copie du plateau initial pour pouvoir annuler le coup
	
	if( player_bis==player1) opponent==player2;
	else opponent==player1;
	
	while(courant!=NULL) // Pour chaque pion pouvant être joué
	{
		for(i=0;i<6;i++) // Essayer les 6 mouvements
		{
			switch(i)
			{
				case 0 : result = move_possible( courant->p1, courant->p2, courant->p3, left, T_bis,player_bis);
					dep=left;
					break;
				case 1 : result = move_possible( courant->p1, courant->p2, courant->p3, right, T_bis,player_bis);
					dep=right;
					break;
				case 2 : result = move_possible( courant->p1, courant->p2, courant->p3, up_left, T_bis,player_bis);
					dep=up_left;
					break;
				case 3 : result = move_possible( courant->p1, courant->p2, courant->p3, up_right, T_bis,player_bis);
					dep=up_right;
					break;
				case 4 : result = move_possible( courant->p1, courant->p2, courant->p3, down_left, T_bis,player_bis);
					dep=down_left;
					break;
				case 5 : result = move_possible( courant->p1, courant->p2, courant->p3, down_right, T_bis,player_bis);
					dep=down_right;
					break;
				default : break;
			}
			if(result != impossible) 
				move( courant->p1, courant->p2, courant->p3, dep,result,T_bis);	
			else
				continue; // On passe à l'itération suivante du if
				
			tmp=Min( T_bis, depth, alpha, beta, opponent);
			
			if(tmp>Max_val) // Un nouveau "meilleur coup" a été trouvé
			{
				Max_val = tmp;
				result_dep=dep;
				p1->x = courant->p1.x; p1->y = courant->p1.y;
				p2->x = courant->p2.x; p2->y = courant->p2.y;
				p3->x = courant->p3.x; p3->y = courant->p3.y;
				
			}
			copy_tab(T_bis,T_tmp); //Annulation du coup effectué.
		}
		courant=courant->suivant;
	}
	return result_dep;
}	

//////////MAIN//////////
int main ()
{
	COORD pos1,pos2,pos3;
	MOVEMENT mvt;
	lc liste=NULL; //Initialisation liste c
	srand(time(NULL)); //Permet d'avoir un vrai aléatoire
	init_tab(daisy);
	liste = gather_pions_possible(T_reference,current_player);
	affichage_lc(liste);
	affiche(T_reference);
	
	mvt = alpha_beta(T_reference, 2, -10000, 10000, player2, &pos1, &pos2, &pos3);
	printf("Résultat IA : \nMouvement : %d\n", mvt);
	printf("(%d,%d) ", pos1.x, pos1.y);
	printf("(%d,%d) ", pos2.x, pos2.y);
	printf("(%d,%d) \n", pos3.x, pos3.y);
	printf("\n");
	affiche(T_reference);
	
	return 0;	
}

/*
int main(int argc, char *argv[])
{
	FILE* fichier_score = NULL;
	char pseudo1[16], pseudo2[16];
	char all_score[TAILLE_MAX] = ""; 
	START_POSITION mode_de_jeu;
	
	printf("Choississez votre pseudo joueur n°1");
	scanf("%s",pseudo1);	
	printf("Choississez votre pseudo joueur n°2");
	scanf("%s",pseudo2);
	//Il faut afficher à l'écran les pseudos en début de partie. ( partie graphique nécessaire ).
	
	printf("En combien de pion gagnants voulez jouer la partie ?");
	scanf("%d",condition_pion);
	
	printf("Souhaitez vous jouer en nombre de coup limité ? Si oui, indiquez le nombre de coup total maximum, si non faites -1");
	scanf("%d",condition_coup);
	
	printf("Mode de jeu disponible : standart, domination, face à face, daisy, snake, alliance, labyrinthe ou aléatoire");
	scanf("%d",mode_de_jeu);
	init_tab(mode_de_jeu); //T_reference est alors initialisé selon le mode de jeu sélectionné.
	
	while (is_victory()==0)
	{
		//Fonction jouer un coup, changer le player à la fin du coup.
		//Si condition_coup!=-1 alors il faut décrémenter condition_coup à chaque coup.
	}
	
	//Fichier_score doit être ouvert en fin de partie pour enregistrer le score de la partie et afficher les anciens scores.
	fichier_score = fopen("fichier_score.txt", "r+"); //r+ pour lire et écrire dans le fichier, r pour lire et w pour écrire uniquement.
	if ( fichier_score != NULL)
	{
		fprintf(fichier_score,"%s : %d-%d : %s\n", pseudo1, score1, score2, pseudo2);
		while(fgets(all_score, TAILLE_MAX, fichier_score) != NULL) //Parcours tout le fichier des scores.
		{
			//Affiche le tableau des scores en fin de partie. ( partie graphique nécessaire ).
		}
		fclose(fichier_score);
	}
	else printf("Impossible d'ouvrir le fichier des scores.");
	
	return 0;
}
*/
