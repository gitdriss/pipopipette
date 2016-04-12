/* Défini la structure de la grille et les fonctions qui permettent de la manipuler */


#ifndef _GRILLE_H_
#define _GRILLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "common.h"

/*******************************************************************************
*				Stuctures - Macros			       *
*******************************************************************************/

/* structure de la matrice (exemple 3x3):
-1  1 -1  1 -1  1 -1		|  c: titulaire de la case (cf code joueur)
 1  c  0  c  0  c  1		| -1: coin
-1  0 -1  0 -1  0 -1		|  0: vide
 1  c  0  c  0  c  1		|  1: barre
-1  0 -1  0 -1  0 -1		|
 1  c  0  c  0  c  1		|
-1  1 -1  1 -1  1 -1		|
*/
typedef int matrix[ (2*NX+1)*(2*NY+1) ];

/* macro d'accès à la structure */
#define grille(i,j) grille[i*(2*NY+1)+j]

/* Code joueur */
#define OP -5
#define AI 5


/*******************************************************************************
*				Fonctions				       *
*******************************************************************************/

/* Création de la matrice */
void createMatrix(matrix grille);

/* Ajoute un move à la matrice, retourne le nombre de cases que ferme le move */
int addMove(matrix grille, move* mv, int tour);

/* Supprime un move de la matrice */
void delMove(matrix grille, move* mv);

/* Affiche la matrice */
void printMatrix(matrix grille);
void printM(matrix grille);

#endif
