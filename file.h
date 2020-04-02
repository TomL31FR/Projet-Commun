#ifndef _FILE_H_
#define _FILE_H_

#include "const.h"
#include "cellule.h"

typedef struct {
    int taille;
    int tete;
    int queue;
    cellule_t **tab;
} file_t;

void initialiser_file(file_t* file, int taille);
void detruire_file(file_t* file);
int taille_file(file_t file);
bool file_vide(file_t file);
bool file_pleine(file_t file);
void enfiler(file_t* file, cellule_t* cellule);
cellule_t *defiler(file_t* file);

#endif