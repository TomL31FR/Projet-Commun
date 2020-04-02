#include "thread.h"
#include "socket.h"

void *thread_serveur(void *arg) {
    /* Déclarations */
    int port, 
        sockfd, 
        largeur, 
        hauteur,
        sock_client1,
        sock_client2;
    struct sockaddr_in adresse_serveur;
    arguments_thread_serveur *args;

    /* Récupération de la structure pour le déroulement de la partie */
    args = (arguments_thread_serveur*)arg;
    port = args->port;
    largeur = args->largeur;
    hauteur = args->hauteur;

    /* Création de la socket TCP de la partie */
    creer_adresse_serveur(&adresse_serveur, port);
    sockfd = creer_socket_tcp();
    nommer_socket(sockfd, &adresse_serveur);

    /* Le thread côté serveur écoute sur la socket TCP */
    ecouter(sockfd, 2);

    printf("En attente de connexion des joueurs...\n");

    /* 2 clients ont fait une requête, on attend donc 2 joueurs pour la partie donc deux connexions doivent être acceptées */
    sock_client1 = accepter_client(sockfd);
    printf("Connexion avec le joueur 1 établie\n");
    sock_client2 = accepter_client(sockfd);
    printf("Connexion avec le joueur 2 établie\n");

    printf("largeur x hauteur : %d x %d\n", largeur, hauteur);
    printf("sockets client 1 et 2 : %d %d\n", sock_client1, sock_client2);

    fermer_socket(sock_client1);
    fermer_socket(sock_client2);

    return NULL;
}