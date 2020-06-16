#include "connexionTCP.h"

int main(int argc, char const *argv[])
{
	//Le timing est passé en argument
	if (argc > 1)
	{
		//Si le timing a été entré en paramètres
		startServeur(argv[1]);
	}else{
		//Sinon on choisit un timing par défaut qui est 10
		startServeur("10");
	}

    //Detruire le serveur
    destroyServeur();

    return EXIT_SUCCESS;
}