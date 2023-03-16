#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/minishell.h"

// typedef struct s_list_
// {
// 	char	*arg;
// 	t_list	prev;
// 	t_list	next;
// }			t_list;

typedef struct s_shell
{
	char	*input;
	char	**parse;
	//t_list	list;
	int		squote;
	int		dquote;
}		t_shell;

int count_dquote(char *input)
{
	int	i;
	int	res;

	i = 0;
	res=0;
	while (input[i])
	{
		if (input[i] == '"')
			res++;
	}
	res = res % 2;
	return (res);
}

char **parsing(t_shell shell)
{
	int	i;
	char *temp;
	shell.dquote = 0;

	i = 0;
	shell.parse = ft_split(shell.input, ' ');
	while (count_dquote(shell.parse[i]) > 0)
	{
		temp = readline(">");
		if (count_dquote(shell.parse[i]) > 0)
			break;
	}
		//else if (ft_strchr(shell.parse[i], '"') != NULL
	return (shell.parse);
}

int main()
{
	t_shell shell;

    // Boucle de lecture d'entrée utilisateur
    while (1) {
        // Utilise readline pour lire l'entrée utilisateur
        shell.input = readline("minishell$ ");
		//parsing(shell);
        // Si l'utilisateur entre une chaîne vide, quitte la boucle
        if (!shell.input || !ft_strcmp(shell.input, ""))
            break;
        rl_redisplay();
        // Affiche l'entrée utilisateur et l'ajoute à l'historique
        //printf("Vous avez entré : %s\n", shell.input);
		//ajoute la ligne en historique
        add_history(shell.input);
        // Libère la mémoire allouée pour l'entrée utilisateur
        free(shell.input);
    }
    return 0;
}