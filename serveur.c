#include "const.h"
#include "socket.h"
#include "file.h"
#include <pthread.h>
#include "thread.h"

int main(int argc, char **argv) {
    /* Déclarations */
    int sockfd, 
        portUDP, 
        largeur_grille, 
        hauteur_grille;
    struct sockaddr_in adresse_serveur, 
        *adresse_client, 
        adresse_joueur1, 
        adresse_joueur2;
    reponse_serveur_connexion_client *reponse;
    requete_client_connexion_udp requete;
    arguments_thread_serveur *args;
    file_t file;
    cellule_t *client, 
        *joueur1, 
        *joueur2;
    char adresse[INET_ADDRSTRLEN];
    pthread_t serveur;

    /* Vérification du nombre d'arguments */

    if(argc != 4) {
        fprintf(stderr, "Usage : %s largeur_grille hauteur_grille port \n", argv[0]);
        fprintf(stderr, "Où :\n");
        fprintf(stderr, "   largeur_grille : largeur de la grille de jeu\n");
        fprintf(stderr, "   hauteur_grille : hauteur de la grille de jeu\n");
        fprintf(stderr, "   port : port d'écoute du serveur\n");
        exit(EXIT_FAILURE);
    }

    /* Démarrage du programme du serveur */
    printf("Démarrage du serveur...\n");

    srand(time(NULL));
    initialiser_file(&file, TAILLE_FILE);

    /* Création de la socket UDP */
    printf("Création de la socket UDP...");
    sockfd = creer_socket_udp();
    printf(" OK\n");

    /* Récupération du numéro de port et des dimensions de la grille */
    largeur_grille = atoi(argv[1]);
    hauteur_grille = atoi(argv[2]);
    portUDP = atoi(argv[3]);

    /* Création de l'adresse serveur */
    printf("Création de l'adresse du serveur...");
    creer_adresse_serveur(&adresse_serveur, portUDP);
    printf(" OK\n");

    /* Bind de la socket */
    printf("Nommage de la socket...");
    nommer_socket(sockfd, &adresse_serveur);
    printf(" OK\n");

    /* Affichage des informations du serveur */
    inet_ntop(AF_INET, &adresse_serveur.sin_addr, adresse, INET_ADDRSTRLEN);
    printf("Port d'écoute : %d\n", portUDP);
    printf("Adresse du serveur : %s\n", adresse);
    printf("\nServeur en attente de joueurs...\n");

    /* Réception des clients et démarrage des parties */
    while(true) {

        /* Attente de réception d'une demande de connexion d'un client */
        adresse_client = malloc(sizeof(struct sockaddr_in));
        recevoir_client(sockfd, &requete, adresse_client);

        client = malloc(sizeof(cellule_t));
        if(requete.id_joueur >= 0) {
            printf("Liaison avec client (id %d)...\n", requete.id_joueur);
            initialiser_cellule(client, adresse_client);

            /* On ajoute le client à la file d'attente */
            enfiler(&file, client);
        }

        /* On essaie de créer le plus de parties possible */
        while(taille_file(file) >= 2) {
            /* On sélectionne les deux joueurs en tête de file */
            joueur1 = defiler(&file);
            joueur2 = defiler(&file);
            adresse_joueur1 = *joueur1->adresse;
            adresse_joueur2 = *joueur2->adresse;

            /* Ports TCP dispos -> 1024 à 65535 */
            reponse = malloc(sizeof(reponse_serveur_connexion_client));
            reponse->portTCP = rand()%64511 + 1024;

            args = malloc(sizeof(arguments_thread_serveur));
            args->largeur = largeur_grille;
            args->hauteur = hauteur_grille;
            args->port = reponse->portTCP;

            pthread_create(&serveur, NULL, thread_serveur, (void*)args);
            
            sleep(1);

            envoyer(sockfd, reponse, sizeof(reponse_serveur_connexion_client), &adresse_joueur1);
            envoyer(sockfd, reponse, sizeof(reponse_serveur_connexion_client), &adresse_joueur2);
        }
    }

    /* Code non exécuté à cause de la boucle while(true) */
    printf("Fermeture de la socket UDP...");
    fermer_socket(sockfd);
    printf(" OK\n");

    detruire_file(&file);

    printf("Arrêt du serveur.\n");

    return EXIT_SUCCESS;
}