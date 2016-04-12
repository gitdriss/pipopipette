/* Défini les fonctions permettant de manipuler l'arbre */

#include "algo.h"

short int min(short int a, short int b) {
	return (a<b)? a:b;
}

short int max(short int a, short int b) {
	return (a>b)? a:b;
}

short int alphaBeta(matrix grille, short int alpha, short int beta, short int rec, short int profRec, const short int profondeur, short int joueur, move* mv) {
	
	short int score,val,i,j,jSuivant;
	move* mvTmp;

	if(!profRec) {
		return rec;
	}
	if(joueur==AI) {
		// Tour de l'AI
		
		short int bestVal = -1000;
		
		for(i=1;i<2*NX+1;i+=2) {
			for(j=1;j<2*NY+1;j+=2){
				if( !grille[ i*(2*NY+1) + (j+1)  ] ) { // Coup possible à l'Est
						// Création du move
						mvTmp = (move*)malloc( sizeof(move) );
						mvTmp->x = i/2;
						mvTmp->y = j/2;
						mvTmp->d = E;
				
						// Evaluation
						score = addMove(grille,mvTmp,joueur)*(joueur/AI);
						jSuivant = (score)? joueur:(-joueur);
				
						// Appel Récursif
						val = alphaBeta(grille, alpha, beta, (rec+score), profRec-1, profondeur, jSuivant, mv);
						delMove(grille,mvTmp);
				
						// Selection Move
						if(val>bestVal) {
							bestVal=val;
							if(profRec==profondeur){
								*mv = *mvTmp;
							}
						}
						
						// Coupure beta
						if(bestVal >= beta) {
							return bestVal;
						}
						alpha = max( alpha, val );
						
						// Libération du Move 
						free(mvTmp);
				}
				if( !grille[ (i+1)*(2*NY+1) + j  ] ) { // Coup possible au Sud
						// Création du move
						mvTmp = (move*)malloc( sizeof(move) );
						mvTmp->x = i/2;
						mvTmp->y = j/2;
						mvTmp->d = S;
				
						// Evaluation
						score = addMove(grille,mvTmp,joueur)*(joueur/AI);
						jSuivant = (score)? joueur:(-joueur);
				
						// Appel Récursif
						val = alphaBeta(grille, alpha, beta, (rec+score), profRec-1, profondeur, jSuivant, mv);
						delMove(grille,mvTmp);
				
						// Selection Move
						if(val>bestVal) {
							bestVal=val;
							if(profRec==profondeur){
								*mv = *mvTmp;
							}
						}
						
						// Coupure beta
						if(bestVal >= beta) {
							return bestVal;
						}
						alpha = max( alpha, val);
						
						// Libération du Move 
						free(mvTmp);
				}
			}
		}
	return bestVal;
	} 
	
	else {
		// Tour du joueur adverse
		for(i=1;i<2*NX+1;i+=2) {
			for(j=1;j<2*NY+1;j+=2){
				if( !grille[ i*(2*NY+1) + (j+1)  ] ) { // Coup possible à l'Est
						// Création du move
						mvTmp = (move*)malloc( sizeof(move) );
						mvTmp->x = i/2;
						mvTmp->y = j/2;
						mvTmp->d = E;
				
						// Eval
						score = addMove(grille,mvTmp,joueur)*(joueur/AI);
						jSuivant = (score)? joueur:(-joueur);
				
						// Appel Récursif
						val = min( val, alphaBeta(grille, alpha, beta, (rec+score), profRec-1, profondeur, jSuivant, mv) );
						delMove(grille,mvTmp);
						
						// Coupure alpha
						if( alpha >= val ) {
							return val;
						}
						beta = min( beta, val );
						
						// Libération du Move
						free(mvTmp);
				}
				if( !grille[ (i+1)*(2*NY+1) + j  ] ) { // Coup possible au Sud
						// Création du move
						mvTmp = (move*)malloc( sizeof(move) );
						mvTmp->x = i/2;
						mvTmp->y = j/2;
						mvTmp->d = S;
				
						// Eval
						score = addMove(grille,mvTmp,joueur)*(joueur/AI);
						jSuivant = (score)? joueur:(-joueur);
				
						// Appel Récursif
						val = min( val, alphaBeta(grille, alpha, beta, (rec+score), profRec-1, profondeur, jSuivant, mv) );
						delMove(grille,mvTmp);
						
						// Coupure alpha
						if( alpha >= val ) {
							return val;
						}
						beta = min( beta, val );
						
						// Libération du Move
						free(mvTmp);
				}
			}
		}
	return val;
	}
}
