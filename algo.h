/* Défini la structure de l'arbre et les fonctions permettant de le manipuler */

#ifndef _ALGO_H_
#define _ALGO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "common.h"
#include "grille.h"


/*******************************************************************************
*						Stuctures				    						   *
*******************************************************************************/

/* Les profondeurs d'analyse sont déterminées à l'aide du fichier ods présent 
dans le dossier.

Il s'agit d'analyser le nombre d'appels maximum de la fonction récursive en
fonction du nombre de coups possibles restant et de la profondeur d'analyse.

L'évolution de la profondeur d'analyse est ensuite choisie en se basant sur la 
limite trouvée au premier coup (4 pour l'alphaBeta, 3 pour le minMax).

Cependant, la présence des coupures alpha et beta dans le programme  complique
cette étude, car selon le jeu, l'élagage sera plus ou moins efficace, ainsi 
l'évaluation risque dans certains cas de dépasser le temps imparti.

Nous avons donc pris le parti de choisir des valeurs médianes au début du jeu,
et de prendre un peu plus de risque vers la fin de la partie, en supposant que
le nombre de coupures réalisées seront plus nombreuses.

Des test on bien sûr étés réalisés pour vérifier que le programme fonctionnait
correctement, toutefois il n'est pas à l'abri d'une situation qui demanderai un
temps de calcul trop long.

L'implémentation d'une méthode de vérification du temps permettrai de remédier à 
ce problême */

#define P144 3
#define P92 4
#define P56 5
#define P31 6
#define P21 7
#define P16 8
#define P13 9
#define P12 11

/*******************************************************************************
*						Fonctions		 									   *
*******************************************************************************/

short int alphaBeta(matrix grille, short int alpha, short int beta, short int rec, short int profRec, const short int profondeur, short int joueur, move* mv);

short int min(short int a, short int b);

short int max(short int a, short int b);

#endif
