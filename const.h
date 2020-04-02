#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>

#ifndef _CONST_H_
#define _CONST_H_

/* Constante pour la taille de la file d'attente */

#define TAILLE_FILE 150

/* Constantes pour la sous fenêtre d'informations */

#define HAUTEUR_I 3
#define LARGEUR_I LARGEUR_M + LARGEUR_T + 2
#define POSX_I 1
#define POSY_I 2

/* Constantes pour la fenêtre de simulation */

#define LARGEUR_M 30
#define HAUTEUR_M 15
#define POSX_M 1
#define POSY_M HAUTEUR_I + 4

/* Constantes pour la fenêtre d'outils */

#define LARGEUR_T 15
#define HAUTEUR_T HAUTEUR_M
#define POSX_T LARGEUR_M + 3
#define POSY_T POSY_M

/* Constante pour la taille de la matrice */

#define MAT_SIZE LARGEUR_M*HAUTEUR_M

/* Constante pour les etats des cellules de la grille */

#define LIBRE 0
#define ROUTE 1
#define VOITURE 2

/* Constantes pour la voiture */

#define VITESSE 50
#define HAUT 0
#define DROITE 1
#define BAS 2
#define GAUCHE 3

/* Constante de succès ou d'échec d'une opération */

#define SUCCES 0
#define ECHEC 1

#endif