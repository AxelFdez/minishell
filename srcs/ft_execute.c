
#include "../includes/minishell.h"

int ft_lst_strchr_meta(t_list *list)
{
	t_list *temp;
	temp = list;

	while (temp)
	{
		if (ft_strchr(temp->str, '|') != NULL)
			return (0);
		else if (ft_strchr(temp->str, '>') != NULL)
			return (0);
		else if (ft_strchr(temp->str, '<') != NULL)
			return (0);
		temp = temp->next;
	}
	return (1);
}

// check_herringbone(t_parsing *parse)
// {
// 	if (ft_strcmp(parse->lst_cmdline->str, "<") == 0)
// 		input_redirection();
// 	else if (ft_strcmp(parse->lst_cmdline->str, ">") == 0)
// 		output_redirection();
// 	else if (ft_strcmp(parse->lst_cmdline->str, "<<") == 0)
// 		ft_heredoc();
// 	else if (ft_strcmp(parse->lst_cmdline->str, ">>") == 0)
// 		ft_append();

// }

int check_builtin_input(t_parsing * parse)
{
	char	*tmp;

	tmp = parse->lst_cmdline->str;
	if (ft_strcmp(tmp, "env") == 0 || ft_strcmp(tmp, "ENV") == 0
		|| ft_strcmp(tmp, "export") == 0 || ft_strcmp(tmp, "pwd") == 0
		|| ft_strcmp(tmp, "PWD") == 0 || ft_strcmp(tmp, "echo") == 0)
	{
		return (0);
	}
	return (1);
}

// void builtin_behaviour(t_parsing *parse)
// {
// 	execute_built_in(parse);
// }

void execute_cmd(t_parsing *parse)
{
	// 1- watch on redirection
	// 2 execute cmd
	// 3 where ?
	pid_t child;
	child = fork();
	//char *built_temp;

	if (child < 0)
		perror("fork error\n");
	else if (child == 0)
	{
		// redirection here
		//check_herringbone(parse);
		// printf("command = %s \n", parse->lst_cmdline->str);
		// exit (EXIT_FAILURE);
		if (check_builtin_input(parse) == 1)
			parsing_cmd(parse);
		// else
		// {
		// 	built_temp = parse->lst_cmdline->str;
		// 	// attribuer a une variable la commande builtin. effacer la liste utilisée
		// }
		if (ft_lst_strchr_meta(parse->lst_cmdline) == 0)
			pipex(parse);
	// 	int i = 0;
	// while (parse->command[i])
	// {
	// 	printf("cmd[%d] = %s\n", i, parse->command[i]);
	// 	i++;
	// }
	// ft_lstprint_from_head(parse->lst_cmdline);
	//  exit(EXIT_FAILURE);
		//printf("BP\n");
		execute_built_in(parse);
		//ft_lstprint_from_head(parse->lst_cmdline);
		execve(parse->command[0], parse->command, parse->env);
		perror("command not found");
	}
	wait(NULL);
	// printf("cmd = %s\n", parse->command[0]);
		// int i = 0;
		// while (parse->command[i])
		// {
		// 	free(parse->command[i]);
		// 	i++;
		// }
		// free(parse->command);
	//to_free(parse->command, 0);
	return ;
}

