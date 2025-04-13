#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

int sock = 0;
char pseudo[50];

void *receive_messages(void *arg) {
    char buffer[BUFFER_SIZE];
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int valread = recv(sock, buffer, BUFFER_SIZE - 1, 0);
        if (valread <= 0) {
            printf("Connexion au serveur perdue.\n");
            exit(1);
        }
        printf("%s", buffer);
        fflush(stdout);
    }
    return NULL;
}

int main(int argc, char const *argv[]) {
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char message[BUFFER_SIZE];

    if (argc != 3) {
        fprintf(stderr, "Usage : %s <nom_de_domaine|ip> <port>\n", argv[0]);
        return 1;
    }

    // Résolution de l'hôte
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "Erreur : hôte non trouvé.\n");
        return 1;
    }

    int port = atoi(argv[2]);

    // Création de la socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket failed");
        return 1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    // Connexion au serveur
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return 1;
    }

    printf("Connecté au serveur %s:%d\n", argv[1], port);

    // Demander un pseudo
    printf("Entrez votre pseudo : ");
    fgets(pseudo, sizeof(pseudo), stdin);
    pseudo[strcspn(pseudo, "\n")] = 0; // retirer le \n

    // Envoyer le pseudo au serveur
    send(sock, pseudo, strlen(pseudo), 0);

    // Créer une thread pour recevoir les messages
    pthread_t recv_thread;
    pthread_create(&recv_thread, NULL, receive_messages, NULL);

    // Envoyer des messages
    while (1) {
        memset(message, 0, sizeof(message));
        fgets(message, sizeof(message), stdin);

        char full_msg[BUFFER_SIZE];
        snprintf(full_msg, sizeof(full_msg), "%s : %s", pseudo, message);

        send(sock, full_msg, strlen(full_msg), 0);
    }

    close(sock);
    return 0;
}
