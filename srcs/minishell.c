#include "../includes/minishell.h"

static void	ft_retrieve_env(t_parsing *parse, char **env)
{
	int	i;
	t_list	*new;

	parse->lst_env = NULL;
	i = 0;
	while (env[i])
	{
		new = ft_lstnew(env[i]);
		ft_lstadd_back(&parse->lst_env, new);
		i++;
	}
}


int	main(int ac, char **av, char **env)
{
	t_parsing	parse;

	(void)av;
	parse.env = env;
	if (ac == 1)
	{
		ft_initialization(&parse);
		ft_retrieve_env(&parse, env);
		while (1)
		{
			signal(SIGQUIT, SIG_IGN);
			signals_();
			parse.input = readline("minishell$ ");
			ft_quotes(&parse);
			add_history(parse.input);
			if (ft_check_syntax(&parse))
				ft_get_cmdline(&parse);
			int i = 0;
			t_list *temp;
			temp = parse.lst_cmdline;
			while (temp)
			{
				if (strchr(temp->str, "|") != NULL)
					execute_pipe_cmd(&parse);
				temp = temp->next;
				if (temp == NULL)
					execute_cmd(&parse);
			}
			ft_lstdel_all(&parse.lst_cmdline);
			parse.lst_target = 0;
		}
	}
	puts("end");
	system("leaks minishell");
	return (0);
}
