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

/**
 * Initialise une file vide
 * file : pointeur vers la file à initialiser (file_t*)
 * taille : taille maximale de la file (int)
 */
void initialiser_file(file_t* file, int taille);

/**
 * Détruit le contenu de la file et libère la mémoire allouée par le contenu de la file
 * file : pointeur vers la file à détruire (file_t*)
 */
void detruire_file(file_t* file);

/**
 * Retourne la taille courante de la file
 * file : variable correspondant à la file (file_t)
 */
int taille_file(file_t file);

/**
 * Retourne vrai si la file est vide, faux sinon
 * file : variable correspondant à la file (file_t)
 */
bool file_vide(file_t file);

/**
 * Retourne vrai si la file est pleine, faux sinon
 * file : variable correspondant à la file (file_t)
 */
bool file_pleine(file_t file);

/**
 * Enfile un élément en queue de file
 * file : pointeur vers la file à modifier (file_t*)
 * cellule : cellule contenant l'élément à enfiler (cellule_t*)
 */
void enfiler(file_t* file, cellule_t* cellule);

/**
 * Défile l'élément en tête de la file et retourne l'élément défilé
 * file : pointeur vers la file à modifier (file_t*)
 */
cellule_t *defiler(file_t* file);

#endif