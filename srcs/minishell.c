#include "../includes/minishell.h"

static void	ft_retrieve_env(t_parsing *parse, char **env)
{
	int		i;
	t_list	*new;

	parse->lst_env = NULL;
	i = 0;
	while (env[i])
	{
		new = ft_lstnew(ft_strdup(env[i]));
		ft_lstadd_back(&parse->lst_env, new);
		i++;
	}
}

void	exit_in_cmdline(t_parsing *parse)
{
	if (ft_strcmp(parse->lst_cmdline->str, "exit") == 0)
	{
		if (ft_lst_strchr_pipe(parse->lst_cmdline) != 0)
			ft_exit(parse);
		else
		{
			ft_lstdel_front(&parse->lst_cmdline);
		}
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
			parse.input = readline("\033[3;36mminishell ->\033[0m ");
			ft_quotes(&parse);
			add_history(parse.input);
			//if (ft_check_syntax(&parse))
				ft_get_cmdline(&parse);
			cd_in_cmdline(&parse);
			//exit_in_cmdline(&parse);
			if (parse.lst_cmdline)
			{
				execute_cmd(&parse);
				ft_lstdel_all(&parse.lst_cmdline);
			}
			//system("leaks minishell");
			parse.tmp_ret_value = parse.ret_value;
			if (parse.str_tmp)
				free(parse.str_tmp);
		}
	}
	puts("end");
	system("leaks minishell");
	return (0);
}
// RED = \033[1;31m
// GREEN = \033[1;32m
// YELLOW = \033[1;33m
// DEFAULT = \033[0m