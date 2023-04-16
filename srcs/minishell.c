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

// int ft_lexer(t_parsing *parse)
// {
// 	t_list *temp;
// 	temp = parse->lst_cmdline;

// 	// print_list(temp);
// 	// exit(1);
// 	if ((ft_strcmp(temp->str, ">") == 0 || ft_strcmp(temp->str, "<") == 0 ||
// 		ft_strcmp(temp->str, ">>") == 0 || ft_strcmp(temp->str, "<<") == 0)
// 		&& !temp->next)
// 	{
// 		printf("minishell: syntax error near unexpected token `newline'\n");
// 		return (1);
// 	}
// 	while (temp)
// 	{
// 		if (ft_strcmp(temp->str, "|") == 0)
// 		{
// 			if (!temp->prev || !temp->next)
// 			{
// 				printf("minishell: syntax error near unexpected token `|'\n");
// 				return (1);
// 			}
// 			else if (ft_strcmp(temp->prev->str, "<") == 0 && ft_strcmp(temp->prev->str, "<<") == 0
// 				&& ft_strcmp(temp->prev->str, ">") == 0 && ft_strcmp(temp->prev->str, ">>") == 0)
// 			{
// 				printf("minishell: syntax error near unexpected token `|'\n");
// 				return (1);
// 			}
// 		}
// 		else if (ft_strcmp(temp->str, ">") == 0)
// 		{
// 			if (ft_strcmp(temp->next->str, "<") == 0)
// 				printf("minishell: syntax error near unexpected token `<'\n");
// 			else if (ft_strcmp(temp->next->str, "<<") == 0)
// 				printf("minishell: syntax error near unexpected token `<<'\n");
// 		}
// 		else if (ft_strcmp(temp->str, "<>") == 0)
// 		{
// 			if (ft_strcmp(temp->next->str, ">") == 0 && ft_strcmp(temp->next->str, "<") == 0
// 				&& ft_strcmp(temp->next->str, ">>") == 0 && ft_strcmp(temp->next->str, "<<") == 0)
// 				printf("minishell: syntax error near unexpected token `%s'\n", temp->next->str);
// 		}
// 		temp = temp->next;
// 	}
// 	return (0);
// }

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
			ft_get_cmdline(&parse);
			parse.env = ft_lst_to_char_tab(parse.lst_env);
			// if (ft_lexer(&parse) == 0)
				execute_cmd(&parse);
			free_str_tab(parse.env);
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