#include "cellule.h"
#include "const.h"

void initialiser_cellule(cellule_t *cellule, struct sockaddr_in *adresse) {
    if(cellule != NULL && adresse != NULL) cellule->adresse = adresse;
    else {
        fprintf(stderr, "Erreur lors de l'initialisation de la cellule\n");
        exit(EXIT_FAILURE);
    }
    
}