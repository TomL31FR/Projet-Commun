#ifndef _STRUCTURES_H_
#define _STRUCTURES_H_

typedef struct {
    pid_t id_joueur;
} requete_client_connexion_udp;

typedef struct {
    int portTCP;
} reponse_serveur_connexion_client;

typedef struct {
    int largeur,
        hauteur, 
        port;
} arguments_thread_serveur;

#endif