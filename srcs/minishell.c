#include "../includes/minishell.h"






int main()
{
    // char *input;
    t_parsing   parse;
    // int   db_coat = 0;

    // Boucle de lecture d'entrée utilisateur
    while (1) {
        // Utilise readline pour lire l'entrée utilisateur
        parse.input = readline("minishell$ ");
		// parsing ici
	    // printf("%s\n", input);
        if (!parse.input || !strcmp(parse.input, "")) {
            break;
        }

        ft_get_cmdline(&parse);
        // Si l'utilisateur entre une chaîne vide, quitte la boucle
        // Affiche l'entrée utilisateur et l'ajoute à l'historique
        // printf("Vous avez entré : %s\n", input);
		//ajoute la ligne en historique
        // add_history(input);
        // Libère la mémoire allouée pour l'entrée utilisateur
        // free(parse.input);
    }
    
    puts("end");
    system("leaks minishell");
    return 0;
}