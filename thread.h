#ifndef _THREAD_H_
#define _THREAD_H_

#include "const.h"

/**
 * Thread exécuté une fois qu'au minimum 2 clients aient émis une requête de jeu permettant d'établir une partie
 * arg : arguments du thread (void*)
 */
void *thread_serveur(void *arg);

#endif