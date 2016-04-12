#ifndef _PIPOCOM_
#define _PIPOCOM_

#include "common.h"


/* Initialisation de la connection, à écrire au début de votre main :
int sd;
sd=c_init_connect(); */
int  c_init_connect  () ;

/* Envoi du nom à l'arbitre :
   c_envoie_nom("babypipo",sd); */
void c_envoie_nom(char Nom[],int sd);

/* Récupération du mode de jeu (RCV, SND ou RES) envoyé par l'arbitre*/
modcode c_receive_mode (int sd);

/* Envoie du "move" */
void c_envoie_move(move m, int sd);

/* Réception du "move" joué par l'adversaire */
move c_receive_mv(int sdx);

/* Permet de recevoir votre numéro de joueur 
'A' pour le joueur A et 
'B' pour le joueur B
char cjo;
cjo=c_receive_num(sd);
*/
char c_receive_num(int sdx);

/* Permet de recevoir le résultat du jeu
renvoie 'A' si le joueur A gagne
renvoie 'B' si le joueur B gagne
char gagnant;
gagnant = c_receive_result(sd);
*/
char c_receive_result(int sdx);

/* Fermeture de la connection,à écrire obligatoirement à la fin de votre main :
c_clean_socket(sd,-1,-1);*/
void c_clean_socket (int sd1,int sd2, int sd3);
#endif
