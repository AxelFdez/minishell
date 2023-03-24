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
	if (ac == 1)
	{
		ft_initialization(&parse);
		ft_retrieve_env(&parse, env);
		while (1)
		{
			// parse.input = readline("\033[3;36mminishell ->\033[0m ");
			parse.input = readline("\033[3;34mmin\033[1;37mish\033[1;31mell ->\033[0m ");
			ft_quotes(&parse);
			add_history(parse.input);
			if (ft_check_syntax(&parse))
				ft_get_cmdline(&parse);
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