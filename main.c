#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


int main()
{
    char *input;

    // Boucle de lecture d'entrée utilisateur
    while (1) {
        // Utilise readline pour lire l'entrée utilisateur
        input = readline("Entrez une chaîne : ");
		// parsing ici
        // Si l'utilisateur entre une chaîne vide, quitte la boucle
        if (!input || !strcmp(input, "")) {
            break;
        }
        // Affiche l'entrée utilisateur et l'ajoute à l'historique
        printf("Vous avez entré : %s\n", input);
		//ajoute la ligne en historique
        add_history(input);
        // Libère la mémoire allouée pour l'entrée utilisateur
        free(input);
    }
    return 0;
}