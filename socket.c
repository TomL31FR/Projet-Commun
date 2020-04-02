#include "socket.h"

/* Commun */

void creer_adresse_serveur(struct sockaddr_in *adresse, int port) {
    memset(adresse, 0, sizeof(struct sockaddr_in));
    adresse->sin_family = AF_INET;
    adresse->sin_addr.s_addr = htonl(INADDR_ANY);
    adresse->sin_port = htons(port);
}

void creer_adresse_client(struct sockaddr_in *adresse, int port, char *adr_serveur) {
    memset(adresse, 0, sizeof(struct sockaddr_in));
    adresse->sin_family = AF_INET;
    adresse->sin_port = htons(port);
    if(inet_pton(AF_INET, adr_serveur, &adresse->sin_addr.s_addr) != 1) {
        perror("Erreur lors de la conversion de l'adresse ");
        exit(EXIT_FAILURE);
    }
}

void nommer_socket(int sockfd, struct sockaddr_in *adresse) {
    if(bind(sockfd, (struct sockaddr*)adresse, sizeof(struct sockaddr_in)) == -1) {
        perror("Erreur lors du nommage de la socket ");
        exit(EXIT_FAILURE);
    }
}

void fermer_socket(int sockfd) {
    if(close(sockfd) == -1) {
        perror("Erreur lors de la fermeture de la socket ");
        exit(EXIT_FAILURE);
    }
}

/* Partie UDP */

int creer_socket_udp() {
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("Erreur lors de la création de la socket ");
        exit(EXIT_FAILURE);
    }
    return sockfd;
}

void recevoir_portTCP(int sockfd, reponse_serveur_connexion_client *reponse, struct sockaddr_in *adresse_serveur) {
    if(recvfrom(sockfd, reponse, sizeof(reponse_serveur_connexion_client), 0, NULL, 0) == -1) {
        perror("Erreur lors de la réception du port TCP ");
        exit(EXIT_FAILURE);
    }
}

void recevoir_client(int sockfd, requete_client_connexion_udp *requete, struct sockaddr_in *adresse_client) {
    socklen_t longueur_adresse;
    longueur_adresse = sizeof(struct sockaddr_in);

    if(recvfrom(sockfd, requete, sizeof(requete_client_connexion_udp), 0, (struct sockaddr*) adresse_client, &longueur_adresse) == -1) {
        perror("Erreur lors de la réception de la reqûete du client ");
        exit(EXIT_FAILURE);
    }
}

void envoyer(int sockfd, void *contenu, int taille_contenu, struct sockaddr_in *adresse) {
    if(sendto(sockfd, contenu, taille_contenu, 0, (struct sockaddr*)adresse, sizeof(struct sockaddr_in)) == -1) {
        perror("Erreur lors de l'envoi du message ");
        exit(EXIT_FAILURE);
    }
}

/* Partie TCP */

int creer_socket_tcp() {
    int sockfd;
    if((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))== -1) {
        perror("Erreur lors de la création de la socket ");
        exit(EXIT_FAILURE);
    }
    return sockfd;
}

void ecouter(int sockfd, int n_connexions) {
    if(listen(sockfd, 1) == -1) {
        perror("Erreur lors de la mise en mode passif ");
        exit(EXIT_FAILURE);
    }
}

int accepter_client(int sockfd) {
    int sock_client;
    sock_client = accept(sockfd, (struct sockaddr*)NULL, NULL);
    if(sock_client == -1) {
        perror("Erreur lors de la demande de connexion ");
        exit(EXIT_FAILURE);
    }
    return sock_client;
}

void connecter(int sockfd, struct sockaddr_in *adresse, int taille) {
    if(connect(sockfd, (struct sockaddr*)adresse, taille) == -1) {
        perror("Erreur lors de la connexion ");
        exit(EXIT_FAILURE);
    }
}

void lire(int sock_client, void *arg, int taille) {
    ssize_t lus;
    lus = read(sock_client, arg, taille);
    if(lus == -1) {
        perror("Erreur lors de la lecture ");
        exit(EXIT_FAILURE);
    }
}

void ecrire(int sockfd, void *arg, int taille) {
    ssize_t ecris;
    ecris = write(sockfd, arg, taille);
    if(ecris == -1) {
        perror("Erreur lors de l'envoi ");
        exit(EXIT_FAILURE);
    }
}