/* Défini les fonctions qui permettent de manipuler la structure grille */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "common.h"
#include "grille.h"

void createMatrix(matrix grille) {

	int i,j;

	for (i=0;i<2*NX+1;i++) {
		for(j=0;j<2*NY+1;j++) {
		//Coin : les deux coordonnées sont pair
			if( (i%2==0) && (j%2==0) ) {
				grille(i,j) = -1;
			}
/*		//Cases Joueurs : les deux coordonnées sont impair
			else if( (i%2==1) && (j%2==1) ){
				grille(i,j) = 5;
			}*/
		//Bords : l'une des coordonnées est impair et l'autre est un extremum
			else if( ( i==0 || i==2*NX ||  j==0 || j== 2*NY ) && (i%2 || j%2)   ){
				grille(i,j) = 1;
			}
		//Intérieur (une coordonnée pair, l'autre impair)
			else{
				grille(i,j) = 0;
			}
		}
	}

}


/* Ajoute un move à la matrice */
int addMove(matrix grille, move* mv, int joueur){

// joueur vaut -5 si OP, 5 si AI
	int c=0;
	
	// Sécurité
	if(!mv) {
		printf("Erreur addMove: mv==NULL\n");
		return -1;
	}
	
	//East
	if(mv->d==E){
		//Ajout du move
		grille[ (mv->x*2+1)*(2*NY+1) + (mv->y*2+2) ] = 1;

		//test fermeture de case X Y
		if(grille[ (mv->x*2+1)*(2*NY+1) + (mv->y*2) ] == 1) //west?
			if(grille[ (mv->x*2+2)*(2*NY+1) + (mv->y*2+1) ] == 1) //south?
				if(grille[ (mv->x*2)*(2*NY+1) + (mv->y*2+1) ] == 1){ //north?
					grille[ (mv->x*2+1)*(2*NY+1)+(mv->y*2+1) ] = joueur;
					c++;
				}

		//test fermeture de case X Y+1
		if(grille[ (mv->x*2+2)*(2*NY+1) + ((mv->y+1)*2+1) ] == 1) //south?
			if(grille[ (mv->x*2+1)*(2*NY+1) + ((mv->y+1)*2+2) ] == 1) //east?
				if(grille[ (mv->x*2)*(2*NY+1) + ((mv->y+1)*2+1) ] == 1){ //north?
					grille[ (mv->x*2+1)*(2*NY+1)+((mv->y+1)*2+1) ] = joueur;
					c++;
				}

	}

	//West
	else if(mv->d==W){

		grille[ (mv->x*2+1)*(2*NY+1) + (mv->y*2) ] = 1;

		//test fermeture de case X Y
		if(grille[ (mv->x*2+1)*(2*NY+1) + (mv->y*2+2) ] == 1) //east?
			if(grille[ (mv->x*2+2)*(2*NY+1) + (mv->y*2+1) ] == 1) //south?
				if(grille[ (mv->x*2)*(2*NY+1) + (mv->y*2+1) ] == 1){ //north?
					grille[ (mv->x*2+1)*(2*NY+1)+(mv->y*2+1) ] = joueur;
					c++;
				}

		//test fermeture de case X Y-1
		if(grille[ (mv->x*2)*(2*NY+1) + ((mv->y-1)*2+1)] == 1) //north?
			if(grille[ (mv->x*2+2)*(2*NY+1) + ((mv->y-1)*2+1) ] == 1) //south?
				if(grille[ (mv->x*2+1)*(2*NY+1) + ((mv->y-1)*2) ] == 1){ //west?
					grille[ (mv->x*2+1)*(2*NY+1)+((mv->y-1)*2+1) ] = joueur;
					c++;
				}

	}

	// South
	else if(mv->d==S) {
		grille[ (mv->x*2+2)*(2*NY+1) + (mv->y*2+1) ] = 1;

		//test fermeture de case X Y
		if(grille[ (mv->x*2+1)*(2*NY+1) + (mv->y*2) ] == 1) //west?
			if(grille[ (mv->x*2+1)*(2*NY+1) + (mv->y*2+2) ] == 1) //east?
				if(grille[ (mv->x*2)*(2*NY+1) + (mv->y*2+1) ] == 1){ //north?
					grille[ (mv->x*2+1)*(2*NY+1)+(mv->y*2+1) ] = joueur;
					c++;
				}

		
		//test fermeture de case X+1 Y
		if(grille[ ((mv->x+1)*2+1)*(2*NY+1) + (mv->y*2) ] == 1) //west?
			if(grille[ ((mv->x+1)*2+1)*(2*NY+1) + (mv->y*2+2) ] == 1) //east?
				if(grille[ ((mv->x+1)*2+2)*(2*NY+1) + (mv->y*2+1) ] == 1){ //south?
					grille[ ((mv->x+1)*2+1)*(2*NY+1)+(mv->y*2+1) ] = joueur;
					c++;
				}

	}

	//North
	else if(mv->d==N){
		grille[ (mv->x*2)  *(2*NY+1) + (mv->y*2+1) ] = 1;

		//test fermeture de case X Y
		if(grille[ (mv->x*2+1)*(2*NY+1) + (mv->y*2) ] == 1) //west?
			if(grille[ (mv->x*2+2)*(2*NY+1) + (mv->y*2+1) ] == 1) //south?
				if(grille[ (mv->x*2+1)*(2*NY+1) + (mv->y*2+2) ] == 1){ //east?
					grille[ (mv->x*2+1)*(2*NY+1)+(mv->y*2+1) ] = joueur;
					c++;
				}


		//test fermeture de case X-1 Y
		if(grille[ ((mv->x-1)*2+1)*(2*NY+1) + (mv->y*2+2) ] == 1) //east?
			if(grille[ ((mv->x-1)*2+1)*(2*NY+1) + (mv->y*2) ] == 1) //west?
				if(grille[ ((mv->x-1)*2)*(2*NY+1) + (mv->y*2+1) ] == 1){ //north?
					grille[ ((mv->x-1)*2+1)*(2*NY+1)+(mv->y*2+1) ] = joueur;
					c++;
				}

	}
	return c;
}

/* Supprime un move de la matrice */
void delMove(matrix grille, move* mv){

	// Sécurité
	if(!mv) {
		printf("Erreur delMove: mv==NULL\n");
		return ;
	}	
	
	if(mv->d==E){ //East
		grille[ (mv->x*2+1)*(2*NY+1) + (mv->y*2+2) ] = 0;
		grille[ (mv->x*2+1)*(2*NY+1)+(mv->y*2+1) ] = 0;
		grille[ (mv->x*2+1)*(2*NY+1)+((mv->y+1)*2+1) ] = 0;
	}
	if(mv->d==W){ // West
		grille[ (mv->x*2+1)*(2*NY+1) + (mv->y*2) ] = 0;
		grille[ (mv->x*2+1)*(2*NY+1)+(mv->y*2+1) ] = 0;
		grille[ (mv->x*2+1)*(2*NY+1)+((mv->y-1)*2+1) ] = 0;
		}
	if(mv->d==S) {// South
		grille[ (mv->x*2+2)*(2*NY+1) + (mv->y*2+1) ] = 0;
		grille[ (mv->x*2+1)*(2*NY+1)+(mv->y*2+1) ] = 0;
		grille[ ((mv->x+1)*2+1)*(2*NY+1)+(mv->y*2+1) ] = 0;
		}
	if(mv->d==N) {// North
		grille[ (mv->x*2)  *(2*NY+1) + (mv->y*2+1) ] = 0;
		grille[ (mv->x*2+1)*(2*NY+1)+(mv->y*2+1) ] = 0;
		grille[ ((mv->x-1)*2+1)*(2*NY+1)+(mv->y*2+1) ] = 0;
	}
	
	
	
}

/* Affiche la matrice */
void printMatrix(matrix grille){

	int i,j,cpt;

	//Coordonnées des colonnes
	printf("\n ");
	for(i=0;i<NY;i++){ 
		if(i<10)
			printf("   %d",i);
		else
			printf("  %d",i);
	}

	// Affichage de la grille
	for(i=0;i<2*NX+1;i++) {
		// Coordonnées des lignes
		cpt = (i-1)/2;
		if(i%2){
			cpt = (i-1)/2;
			printf("\n%d ",cpt);
		}		
		else
			printf("\n  ");

		// Affichage du contenu
		for(j=0;j<2*NY+1;j++) {
				switch( grille(i,j) ){
					case OP: printf("B"); break;
					case AI: printf("A"); break;
					case -1: printf("+"); break;
					case 0:  printf(" "); break;
					case 1:  
						if(j%2)
							printf("-");
						else
							printf("|");
						break;
				}
		printf(" ");
		}
	}
	printf("\n\n");
}

void printM(matrix grille) {
	int i,j;
	for(i=0;i<2*NX+1;i++) {
		printf("\n");
		for(j=0;j<2*NY+1;j++) {
			printf(" %+d",grille(i,j));
		}
	}
}




