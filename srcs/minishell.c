#include "../includes/minishell.h"

t_sig	sig = {0, 0, 0, 0};

int	ft_main_loop(t_parsing *parse)
{
	while (1)
	{
		sig.child = 1;
		parse->input = readline("minishell -> ");
		if (!parse->input)
		{
			write(2, "exit\n", 5);
			return (127);
		}
		ft_quotes(parse);
		ft_add_history(parse);
		ft_history(parse);
		if (ft_unsupported_token(parse))
			if (ft_get_cmdline(parse))
			{
				parse->env = ft_lst_to_char_tab(parse->lst_env);
				execute_cmd(parse);
				ft_lexer(parse);
				free_str_tab(parse->env);
			}
		ft_lstdel_all(&parse->lst_cmdline);
		free(parse->input);
		parse->tmp_ret_value = parse->ret_value;
	}
	return (0);
}

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
		return (ft_main_loop(&parse));
	}
	return (0);
}
// RED = \033[1;31m
// GREEN = \033[1;32m
// YELLOW = \033[1;33m
// DEFAULT = \033[0m