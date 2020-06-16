#include "connexionTCP.h"

void initServeur()
{
    serveur = (Serveur*)malloc(sizeof(Serveur));

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

void loopServeur()
{
    int newSocket;
    struct sockaddr_in newAddr;
    socklen_t addr_size;

    while(1){

        newSocket = accept(serveur->socketServer, (struct sockaddr*)&newAddr,&addr_size);
        if (newSocket >= 0)
        {   
            //Création d'un processus pour le jeu
            pid_t fils = fork();
            if (fils > 0)
            {
                //On n'a plus besoin du socket du serveur 
                close(serveur->socketServer);
            
                printf("[+]Un joueur vient de se connecter.\n");


                char buffer[TAILLE];
                generateGrille(buffer);

                //Envoyer la grille au joueur
                envoyerMessage(newSocket, buffer);
                while(1){
                    bzero(buffer, TAILLE);
                    if (recv(newSocket, buffer, TAILLE, 0) > 0)
                    {
                        if (strcmp(buffer, QUIT) == 0)
                        {
                            printf("[+]Un joueur vient de se déconnecter.\n");
                            break;
                        }else if (strcmp(buffer, REPLAY) == 0)
                        {
                            generateGrille(buffer);
                            //Envoyer la grille au joueur
                            envoyerMessage(newSocket, buffer);
                        }
                    }
                }
            }
        }
        
            
    }

}

//Méthode pour générer la grille pour les joueurs automatiquement
void generateGrille(char* message){
    int grille[TAILLE_GRILLE][TAILLE_GRILLE] = {0};
    int x, y;
    int tour = 0;
    time_t t;
    srand((unsigned)time(&t));

    for (int i = 1; i <= TAILLE_GRILLE*TAILLE_GRILLE/2; ++i)
    {
        while(tour != 2)
        {
            x = rand()%TAILLE_GRILLE;
            y = rand()%TAILLE_GRILLE;
            if (grille[x][y] == 0)
            {
                grille[x][y] = i;
                tour++;
            } 
        }

        tour = 0;

    }

    bzero(message, TAILLE);
    strcat(message, TIMING);
    strcat(message, ":");
    char tochar[10];
    for (int i = 0; i < TAILLE_GRILLE; ++i)
    {
        for (int j = 0; j < TAILLE_GRILLE; ++j)
        {
            
            bzero(tochar, 10);
            sprintf(tochar, "%d", grille[i][j]);

            strcat(message, tochar);
            strcat(message, " ");
        }
    }
}


void startServeur(const char* timing){
    TIMING = timing;
    initServeur();
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

