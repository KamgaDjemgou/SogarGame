#include "connexionTCP.h"

void initServeur()
{
    serveur = (Serveur*)malloc(sizeof(Serveur));
    serveur->tour = 0;

    struct sockaddr_in serverAddr;
    serveur->socketServer = socket(AF_INET, SOCK_STREAM, 0);

    if(serveur->socketServer < 0)
    {
        printf("[-]Erreur de création du socket du serveur!\n");
        destroyServeur();
    }
    printf("[+]Socket du serveur a été bien créé!\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(IP_SERVEUR);

    if(bind(serveur->socketServer, (struct sockaddr*)&serverAddr,sizeof(serverAddr)) < 0)
    {
        printf("[-]Erreur dans la liaison du socket avec l'adresse\n");
        destroyServeur();
    }

    if(listen(serveur->socketServer, 100) == 0)
    {
        printf("[+]A l'écoute ...\n");
    }

}

void connexionJoueurs()
{
    int newSocket;
    struct sockaddr_in newAddr;
    socklen_t addr_size;

    newSocket = accept(serveur->socketServer, (struct sockaddr*)&newAddr,&addr_size);
    if(newSocket < 0)
    {
        printf("[-]Impossible de connecter le premier joueur\n");
    }else{
        serveur->joueur1.socket = newSocket;
        bzero(serveur->joueur1.pseudo, TAILLE);
        recv(newSocket, serveur->joueur1.pseudo, TAILLE, 0);

        printf("[+]Le joueur %s vient de se connecter.\n",
                serveur->joueur1.pseudo);

    }

    
    envoyerMessage(serveur->joueur1.socket, serveur->joueur2.pseudo);
    envoyerMessage(serveur->joueur2.socket, serveur->joueur1.pseudo);
    
}

void loopServeur()
{
    // char buffer[TAILLE];
    // int tour = 0;
    int newSocket;
    struct sockaddr_in newAddr;
    socklen_t addr_size;

    while(1){

        newSocket = accept(serveur->socketServer, (struct sockaddr*)&newAddr,&addr_size);
        if(newSocket >= 0){
            //Si le premier joueur s'est bien connecté
            serveur->joueur1.socket = newSocket;
            bzero(serveur->joueur1.pseudo, TAILLE);
            //On recoit son nom
            recv(newSocket, serveur->joueur1.pseudo, TAILLE, 0);

            printf("[+]Le joueur %s vient de se connecter.\n",
                    serveur->joueur1.pseudo);

            //Connection du second joueur
            int found = 0;
            do{
                newSocket = accept(serveur->socketServer, 
                (struct sockaddr*)&newAddr,&addr_size);
                if(newSocket >= 0){
                    serveur->joueur2.socket = newSocket;
                    bzero(serveur->joueur2.pseudo, TAILLE);
                    recv(newSocket, serveur->joueur2.pseudo, TAILLE, 0);

                    printf("[+]Le joueur %s vient de se connecter.\n",
                            serveur->joueur2.pseudo);
                    found = 1;
                }

            }while(!found);

            //Création d'un processus fils pour le jeu entre les deux joueurs
            pid_t fils;
            if ((fils = fork()) < 0)
            {
                //Envoyer un message aux clients pour signaler l'erreur
            }else if (fils != 0)
            {
                //On n'a plus besoin du socket du serveur 
                close(serveur->socketServer);

                //On envoie les pseudo de l'adversaire aux joueurs
                envoyerMessage(serveur->joueur1.socket, serveur->joueur2.pseudo);
                envoyerMessage(serveur->joueur2.socket, serveur->joueur1.pseudo);
            }

        }
            
    }

}


void startServeur(){
    initServeur();
    // connexionJoueurs();
    loopServeur();
}

//Fonction pour envoyer un message
int envoyerMessage(int socket, const char* message)
{
    
    return send(socket, message, strlen(message), 0);
}

//Fonction pour recevoir un message
int recevoirMessage(int socket, char* message)
{
    
    return recv(socket, message, strlen(message), 0);
}


//Détruire le serveur pour libérer la mémoire
void destroyServeur()
{
    close(serveur->socketServer);
    serveur = NULL;
    exit(1);
}

