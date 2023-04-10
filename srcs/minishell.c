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
			tcgetattr(STDIN_FILENO, &parse.term);
			parse.term.c_lflag &= ~(ECHOCTL | ICANON);
			tcsetattr(STDIN_FILENO, TCSAFLUSH, &parse.term);
			signal(SIGQUIT, SIG_IGN);
			signals_(0);
			parse.input = readline("minishell -> ");
			if (!parse.input)
				return (0);
			ft_quotes(&parse);
			ft_add_history(&parse);
			ft_history(&parse);
			ft_get_cmdline(&parse);
			// char **cat = malloc(sizeof(char *) * 2);
			// cat[0] = "/bin/cat";
			// cat[1] = "\0";
			// execve("/bin/cat", cat, 0);
			// if (parse.lst_cmdline)
			// {
				parse.env = ft_lst_to_char_tab(parse.lst_env);
				execute_cmd(&parse);
				free_str_tab(parse.env);
			// }
			ft_lstdel_all(&parse.lst_cmdline);
			free(parse.input);
			parse.tmp_ret_value = parse.ret_value;
			//system("leaks minishell");
		}
	}
	return (0);
}
// RED = \033[1;31m
// GREEN = \033[1;32m
// YELLOW = \033[1;33m
// DEFAULT = \033[0m