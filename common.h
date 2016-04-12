/* Définit les constantes globales */
#ifndef COMMON_H
#define COMMON_H


/***********************************
 *  DIMENSION DE LA GRILLE DE JEU  *
 ***********************************/

#define NX 9 //Nombre de colonnes de la grille
#define NY 9 //Nombre de lignes de la grille

/**********************************
 * TYPE de MODE DE JEU RECU DE L'ARBITRE  *
 **********************************/

/* CODE DU MODE (modecode)
//codes que vous devrez utiliser :
RCV (vous devez passer en mode réception)
SND (vous devez passer en mode envoie)
FIN (vous devez receptionner le résultat de la partie)

(cf c_receive_mode  dans pipocom.h)
*/

typedef enum _modcode {RCV,SND,FIN} modcode ;

/***********************************
 *  TEMPS LIMITE POUR JOUER (en s) *
 ***********************************/
#define LIM_TIME 11 


/***********************************
 *  DESCRIPTION D'UN COUP          *
 ***********************************/

/*Orientation pour décrire le coup joué 
N : Nord
W : Ouest
S : Sud
E : Est
*/
typedef enum _orient {none,N,W,S,E} orient ;

/* Le coup
x : indice de colonne de la case jouée (en partant de 0)
y : indice de ligne de la case jouée (en partant de 0)
d : Position du trait par rapport à la case.
*/

typedef struct _move{
	int x;
	int y;
	orient d;
} move ;


#endif
