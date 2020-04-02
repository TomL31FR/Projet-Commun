#include "file.h"
#include <stdlib.h>
#include <stdio.h>

void initialiser_file(file_t *file, int taille) {
    int i;

    if(file == NULL) {
		fprintf(stderr, "Erreur lors de l'initialisation de la file : pointeur NULL\n");
    }

    file->tete = 0;
    file->queue = 0;
    file->taille = taille;
    file->tab = malloc(sizeof(cellule_t*) * file->taille);

    for(i = 0; i < file->taille; i++) {
        file->tab[i] = (cellule_t*)NULL;
    }
}

void detruire_file(file_t *file) {
    while(file->tab[file->tete] != NULL) {
        defiler(file);
    }
    free(file->tab);
}

int taille_file(file_t file) {
    return (file.queue - file.tete) % file.taille;
}

bool file_vide(file_t file) {
	if (file.tab[file.tete] == NULL) return true;
	else return false;
}

bool file_pleine(file_t file) {
    if(file.tete == (file.queue + 1)%file.taille) return true;
    else return false;
}

void enfiler(file_t *file, cellule_t *cellule) {
    if(!file_pleine(*file)) {
        file->tab[file->queue] = cellule;
        file->queue = (file->queue + 1) % file->taille;
    } else {
        fprintf(stderr, "Erreur : file pleine\n");
    }
}

cellule_t* defiler(file_t *file) {
    if(!file_vide(*file)) {
        cellule_t *cellule = file->tab[file->tete];
        file->tete = (file->tete+1) % file->taille;
        return cellule;
    } else {
        return NULL;
    }
} 