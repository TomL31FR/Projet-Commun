#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "const.h"
#include "structures.h"

/* Commun */

/**
 * Permet de créer l'adresse du serveur sans adresse IP prédéfinie (adresse locale 127.0.0.1 utilisée).
 */
void creer_adresse_serveur(struct sockaddr_in *adresse, int port);

/**
 * 
 */
/*
void creer_adresse_serveur_from_ip(struct sockaddr_in *adresse, char *adresse_ip, int port);*/

/**
 * Permet de mémoriser l'adresse du serveur côté client.
 */
void creer_adresse_client(struct sockaddr_in *adresse, int port, char *adr_serveur);

/**
 * Permet de nommer la socket.
 */
void nommer_socket(int sockfd, struct sockaddr_in *adresse);

/**
 * Ferme la socket
 */
void fermer_socket(int sockfd);





/* Partie UDP */

/**
 * Crée une socket UDP
 */
int creer_socket_udp();

/**
 * Permet de recevoir une requête UDP d'un client
 */
void recevoir_client(int sockfd, requete_client_connexion_udp *requete, struct sockaddr_in *adresse_client);

/**
 * Permet de recevoir le port TCP de la partie envoyé par le serveur 
 */
void recevoir_portTCP(int sockfd, reponse_serveur_connexion_client *reponse, struct sockaddr_in *adresse_serveur);

/**
 * Permet d'envoyer un message UDP
 */
void envoyer(int sockfd, void *contenu, int taille_contenu, struct sockaddr_in *adresse);





/* Partie TCP */

/**
 * Permet de créer une socket TCP
 */
int creer_socket_tcp();

/** 
 * Permet d'accepter une connexion TCP
 */
int accepter_client(int sockfd);

/**
 * Permet de mettre la socket en mode écoute
 */
void ecouter(int sockfd, int n_connexions);

/**
 * Permet d'établir la connexion TCP
 */
void connecter(int sockfd, struct sockaddr_in *adresse, int taille);

/**
 * Permet de lire un message TCP dans le flux
 */
void lire(int sock_client, void *arg, int taille);

/**
 * Permet d'écrire un message TCP dans le flux
 */
void ecrire(int sockfd, void *arg, int taille);

#endif