#include "../includes/minishell.h"

static void	ft_add_history(t_parsing *parse)
{
	if (parse->tmp_input == NULL)
		add_history(parse->input);
	else if (ft_strcmp(parse->tmp_input, parse->input) != 0)
	{
		add_history(parse->input);
		free(parse->tmp_input);
	}
	parse->tmp_input = ft_strdup(parse->input);
}

t_sig	sig = {0, 0, 0, 0};



int	main(int ac, char **av, char **env)
{
	t_parsing	parse;
	(void)av;
	if (ac == 1)
	{
		tcgetattr(STDIN_FILENO, &parse.term);
		parse.term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &parse.term);
		signals_func();
		ft_retrieve_env(&parse, env);
		ft_initialization(&parse);
		ft_check_history_size(&parse);
		while (1)
		{
			sig.child = 1;
			parse.input = readline("minishell -> ");
			if (!parse.input)
			{
				write(2, "exit\n", 5);
				return (parse.ret_value);
			}
			ft_quotes(&parse);
			ft_add_history(&parse);
			ft_history(&parse);
			if (ft_unsupported_token(&parse))
			{
				ft_get_cmdline(&parse);
				if (parse.lst_cmdline)
				{
					parse.env = ft_lst_to_char_tab(parse.lst_env);
					execute_cmd(&parse);
					ft_lexer(&parse);
					free_str_tab(parse.env);
				}
			}
			/*Salut ;o)
			Alors j'ai fait en sorte de laisser passer le heredoc...
			Je te laisse voir ca, par contre avec : '<< f /bin/cat | wc -l >' ca affiche bien le message d'erreur 
			mais ca crée qd meme un fichier... 
			J'ai fait aussi une fonction 'ft_unsupported token' pour gerer \ || et ;
			avec message d'erreur et code de retour.
			la par contre ca a du sens de ne pas executer..
			
			Faut voir si ca complique pas trop les choses de laisser passer heredoc avec une commande 
			aui contient des erreurs, je pense que ca ne constitue pas une erreur de le gerer sans exec...
			On verra ca ensemble, j'espere que tu vas trouver les erreurs dont tu parlais hier.
			Force et honneur ;o)*/
			ft_lstdel_all(&parse.lst_cmdline);
			free(parse.input);
			parse.tmp_ret_value = parse.ret_value;
			// system("leaks minishell");
		}
	}
	return (0);
}
// RED = \033[1;31m
// GREEN = \033[1;32m
// YELLOW = \033[1;33m
// DEFAULT = \033[0m