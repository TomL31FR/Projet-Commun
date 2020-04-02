#include "const.h"
#include "socket.h"

int main(int argc, char **argv) {
    /* Déclarations */
    int port_udp, 
        port_tcp, 
        sockfd_udp, 
        sockfd_tcp;
    struct sockaddr_in adresse_serveur_udp,
        adresse_serveur_tcp;
    requete_client_connexion_udp requete;
    reponse_serveur_connexion_client reponse;

    /* Contrôle du nombre d'arguments du programme client */
    if(argc != 3) {
        fprintf(stderr, "Usage : %s adresseIP\n", argv[0]);
        fprintf(stderr, "Où :\n");
        fprintf(stderr, "   adresseIP : adresse IP du serveur\n");
        fprintf(stderr, "   port : port d'écoute du serveur\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    /* Création de la socket UDP côté client */
    sockfd_udp = creer_socket_udp();

    /* Récupération du port sur lequel le serveur écoute */
    port_udp = atoi(argv[2]);

    /* Mémorisation de l'adresse du serveur côté client pour la communication UDP */
    creer_adresse_client(&adresse_serveur_udp, port_udp, argv[1]);

    /* Construction de la requête de connexion */
    requete.id_joueur = getpid();
    
    /* Envoi de la requête */
    envoyer(sockfd_udp, &requete, sizeof(requete_client_connexion_udp), &adresse_serveur_udp);
    printf("En attente d'un joueur...\n");

    /* Réception de la réponse du serveur contenant le port TCP */
    recevoir_portTCP(sockfd_udp, &reponse, &adresse_serveur_udp);

    /* La communication UDP entre le serveur et le client est terminée, on ferme la socket de cette communication côté client */
    fermer_socket(sockfd_udp);
    printf("En attente de connexion avec le serveur...\n");

    port_tcp = reponse.portTCP;
    creer_adresse_client(&adresse_serveur_tcp, port_tcp, argv[1]);
    
    sockfd_tcp = creer_socket_tcp();
    connecter(sockfd_tcp, &adresse_serveur_tcp, sizeof(struct sockaddr_in));

    printf("Connexion établie\n");
    
    return EXIT_SUCCESS;
}