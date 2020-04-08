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
 * Crée l'adresse du serveur sans adresse IP prédéfinie
 * adresse : pointeur vers la structure de l'adresse du serveur (struct sockaddr_in*)
 * port : numéro de port du serveur (int)
 */
void creer_adresse_serveur(struct sockaddr_in *adresse, int port);

/**
 * Mémorise l'adresse du serveur côté client
 * adresse : pointeur vers la structure de l'adresse du serveur (struct sockaddr_in*)
 * port : numéro du port du serveur (int)
 * adr_serveur : adresse IP du serveur
 */
void creer_adresse_client(struct sockaddr_in *adresse, int port, char *adr_serveur);

/**
 * Effectue le nommage (bind) de la socket
 * sockfd : descripteur de fichier associé à la socket (int)
 * adresse : pointeur vers la structure de l'adresse du serveur (struct sockaddr_in*)
 */
void nommer_socket(int sockfd, struct sockaddr_in *adresse);

/**
 * Ferme la socket
 * sockfd : descripteur de fichier associé à la socket (int)
 */
void fermer_socket(int sockfd);





/* Partie UDP */

/**
 * Crée une socket UDP et retourne le descripteur de fichier associé à la socket
 */
int creer_socket_udp();

/**
 * Permet de recevoir une requête UDP d'un client qui souhaite rechercher une partie
 * sockfd : descripteur de fichier associé à la socket (int)
 * requete : pointeur vers la structure qui sera remplie à la réception de la requête (requete_client_connexion_udp*)
 * adresse_client : pointeur de la structure destinée à contenir l'adresse du client qui émet la requête (struct sockaddr_in*)
 */
void recevoir_client(int sockfd, requete_client_connexion_udp *requete, struct sockaddr_in *adresse_client);

/**
 * Permet de recevoir le port TCP de la partie envoyé par le serveur 
 * sockfd : descripteur de fichier associé à la socket (int)
 * reponse : pointeur vers la structure qui sera remplie à la réception de la réponse (reponse_serveur_connexion_client*)
 * adresse_serveur : pointeur de la structure destinée à contenir l'adresse du serveur qui répond à la requête initiale (struct sockaddr_in*)
 */
void recevoir_portTCP(int sockfd, reponse_serveur_connexion_client *reponse, struct sockaddr_in *adresse_serveur);

/**
 * Permet d'envoyer un message UDP
 * sockfd : descripteur de fichier associé à la socket (int)
 * contenu : pointeur vers la structure à envoyer (void*)
 * taille_contenu : taille du contenu du message (int)
 * adresse : pointeur de l'adresse à laquelle le message est envoyé (struct sockaddr_in*)
 */
void envoyer(int sockfd, void *contenu, int taille_contenu, struct sockaddr_in *adresse);





/* Partie TCP */

/**
 * Crée une socket TCP et retourne le descripteur de fichier associé à la socket
 */
int creer_socket_tcp();

/** 
 * Accepte une connexion TCP venant d'un client
 * sockfd : descripteur de fichier associé à la socket (int)
 */
int accepter_client(int sockfd);

/**
 * Permet de mettre la socket en mode écoute (listen)
 * sockfd : descripteur de fichier associé à la socket (int)
 * n_connexions : nombre maximal de requêtes de connexion pouvant être mises en attente avant que les requêtes qui suivent soient refusées (int)
 */
void ecouter(int sockfd, int n_connexions);

/**
 * Permet d'établir la connexion TCP
 * sockfd : descripteur de fichier associé à la socket (int)
 * adresse : pointeur vers l'adresse sur laquelle la connexion est établie (struct sockaddr_in*)
 * taille : taille de l'adresse (int)
 */
void connecter(int sockfd, struct sockaddr_in *adresse, int taille);

/**
 * Permet de lire un message TCP dans le flux
 * sock_client : descripteur de fichier associé à la socket correspondant au client connecté (int)
 * arg : structure destinée à la réception (void*)
 * taille : nombre de bytes lus (int)
 */
void lire(int sock_client, void *arg, int taille);

/**
 * Permet d'écrire un message TCP dans le flux
 * sockfd : descripteur de fichier associé à la socket (int)
 * arg : structure à écrire dans le flux (void*)
 * taille : taille de la structure (int)
 */
void ecrire(int sockfd, void *arg, int taille);

#endif