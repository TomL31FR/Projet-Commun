#ifndef _CELLULE_H_
#define _CELLULE_H_

typedef struct {
    struct sockaddr_in *adresse;
} cellule_t;

/**
 * Initialise une cellule d'une file
 * cellule : pointeur vers la cellule à initialiser, une exception sera lancée si celui-ci est nul
 * adresse : adresse contenue dans la cellule permettant de référencer le client lors de communication UDP
 */
void initialiser_cellule(cellule_t *cellule, struct sockaddr_in *adresse);

#endif