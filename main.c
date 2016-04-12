#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "pipocom.h"
#include "grille.h"
#include "algo.h"
#include <sys/types.h>
#include <unistd.h>

move scanf_move(); //scan un move au clavier

int main() {

	short int sd=-1; //pour communiquer avec l'arbitre
	short int temp, profondeur=P144, rec=0;
	short int nbCoups = 2*NX*NY-NX-NY;
	char nom[50]="YoloSwagTits";
	modcode m=1 ; //mode de jeu
	move mv;
	char cj; //'A' ou 'B';
	char tab_orient[]={'X','N','W','S','E'};
	matrix grille;
	createMatrix(grille);

	//Init des communications (enlever le commentaire pour jouer avec l'arbitre)
	sd=c_init_connect();

	//Envoie des noms
	sprintf(nom,"%s_%d",nom,(int)getpid());
	printf("I'm %s\n",nom);
	c_envoie_nom(nom,sd);

	//Reception du numero du joueur A ou B
	cj = c_receive_num (sd);
	printf("I'm the player %c\n",cj);

	//Reception du mode (RCV/SND/FIN)
	while(nbCoups && m!=FIN) {
		m = c_receive_mode(sd);

		switch(m){
		case RCV:
			printf("Receiving a move...\tnbCoups:%d\n",nbCoups);
			mv = c_receive_mv(sd);
			printf("Move received : %d,%d,%c\n",mv.x,mv.y,tab_orient[(int)mv.d]);
			
			//x-y inversés...
			temp = mv.x;
			mv.x = mv.y;
			mv.y = temp;
			
			//MaJ
			rec+=addMove(grille,&mv,OP);
			break;
		case SND:
			printf("Sending a move...\tnbCoups:%d\n",nbCoups);
			
			// Gestion de la Profondeur
			switch(nbCoups) {
				case 92 : profondeur=P92; break;
				case 56 : profondeur=P56; break;
				case 31 : profondeur=P31; break;
				case 21 : profondeur=P21; break;
				case 16 : profondeur=P16; break;
				case 13 : profondeur=P13; break;
				case 12 : profondeur=P12; break;
			}
			
			alphaBeta(grille, -1000, 1000, rec, profondeur, profondeur, AI, &mv);
			
			//x-y inversés...
			temp = mv.x;
			mv.x = mv.y;
			mv.y = temp;
			
			// Envoi Move
			c_envoie_move(mv,sd);
			
			//x-y inversés...
			temp = mv.x;
			mv.x = mv.y;
			mv.y = temp;
			
			//MaJ
			rec+=addMove(grille,&mv,AI);
			
			printf("Move sent : %d,%d,%c\n",mv.x,mv.y,tab_orient[(int)mv.d]);
			break;
		case FIN:
			printf("Receiving the result of the game...\n");
			break;
		}
		nbCoups--;
	}


	//Fermeture des communications
	c_clean_socket(sd,-1,-1);
	return(0);

	//Astuce pour éviter le warning "unused variable"
	sd--;
}

move scanf_move() {
	//WARNING : scanf non securise
	move m;
	char c;
	printf("Enter move (x,y, N/W/S/E) :");
	scanf("%d %d %c",&m.x,&m.y,&c);
	switch(c) {
		case 'N': m.d=N; break;
		case 'W': m.d=W; break;
		case 'S': m.d=S; break;
		case 'E': m.d=E; break;
		default : m.d=none;
	}
	return(m);
}
