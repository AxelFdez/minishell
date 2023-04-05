#include "../includes/minishell.h"

// static void	ft_retrieve_env(t_parsing *parse, char **env)
// {
// 	int		i;
// 	t_list	*new;

// 	parse->lst_env = NULL;
// 	i = 0;
// 	while (env[i])
// 	{
// 		new = ft_lstnew(ft_strdup(env[i]));
// 		ft_lstadd_back(&parse->lst_env, new);
// 		i++;
// 	}
// }

int	main(int ac, char **av, char **env)
{
	t_parsing	parse;

	(void)av;
	if (ac == 1)
	{
		ft_retrieve_env(&parse, env);
		ft_initialization(&parse);
		ft_check_history_size(&parse);
		while (1)
		{
			signal(SIGQUIT, SIG_IGN);
			signals_();

			parse.input = readline("\033[3;36mminishell ->\033[0m ");
			if (!parse.input)
			{
				printf("exit\n");
				return (0);
			}
			ft_quotes(&parse);
			add_history(parse.input);
			ft_history(&parse);
			ft_get_cmdline(&parse);
			if (parse.input[0] == '$' && parse.lst_cmdline)
				ft_printf("minishell: %s: ", parse.lst_cmdline->str);
			if (parse.lst_cmdline)
			{
				parse.env = ft_lst_to_char_tab(parse.lst_env);
				execute_cmd(&parse);
				free_str_tab(parse.env);
				ft_lstdel_all(&parse.lst_cmdline);
			}
			// system("leaks minishell");
			free(parse.input);
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