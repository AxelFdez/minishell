
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

int ft_lst_strchr_pipe(t_list *list)
{
	t_list *temp;
	temp = list;

	while (temp)
	{
		if (ft_strchr(temp->str, '|') != NULL)
			return (0);
		temp = temp->next;
	}
	return (1);
}

// int	ft_lst_strchr_herringbone(t_list *list)
// {
// 	t_list *temp;
// 	temp = list;

// 	while (temp)
// 	{
// 		if (ft_strchr(temp->str, '>') != NULL)
// 			return (0);
// 		else if (ft_strchr(temp->str, '<') != NULL)
// 			return (0);
// 		temp = temp->next;
// 	}
// 	return (1);
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

int	parsing_built_in(t_parsing *parse)
{
	t_list	*tmp;
	t_list	*tmp2;
	tmp = parse->lst_cmdline;
	tmp2 = parse->lst_cmdline;
	parse->lst_target = 0;

	while (tmp2 && ft_strchr(tmp2->str, '|') == NULL)
	{
		parse->lst_target++;
		tmp2 = tmp2->next;
	}
	while (tmp)
	{
		if (ft_strcmp(tmp->str, "env") == 0 || ft_strcmp(tmp->str, "ENV") == 0)
			return (1);
		if (ft_strcmp(tmp->str, "export") == 0)
			return (2);
		if (ft_strcmp(tmp->str, "pwd") == 0 || ft_strcmp(tmp->str, "PWD") == 0)
			return (3);
		if (ft_strcmp(tmp->str, "echo") == 0)
			return (4);
		tmp = tmp->next;
	}
	return (0);
}

void	input_redirection(t_parsing *parse)
{
	int fd[1];
	ft_lstdel_front(&parse->lst_cmdline);
	// ft_lstprint_from_head(parse->lst_cmdline);
	// exit(EXIT_FAILURE);
	if (access(parse->lst_cmdline->str, F_OK) != 0)
	{
		perror(parse->lst_cmdline->str);
		exit(EXIT_FAILURE);
	}
	if (access(parse->lst_cmdline->str, R_OK) != 0)
	{
		perror(parse->lst_cmdline->str);
		exit(EXIT_FAILURE);
	}
	fd[0] = open(parse->lst_cmdline->str, O_RDONLY);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	ft_lstdel_front(&parse->lst_cmdline);
}

void	output_redirection(t_parsing *parse)
{
	int fd[1];

	ft_lstdel_front(&parse->lst_cmdline);
	fd[0] = open(parse->lst_cmdline->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[0] < 0)
		perror("fd error");
	dup2(fd[0], STDOUT_FILENO);
	close(fd[0]);
	ft_lstdel_front(&parse->lst_cmdline);
}

void	ft_append(t_parsing *parse)
{
	int fd[1];

	ft_lstdel_front(&parse->lst_cmdline);
	fd[0] = open(parse->lst_cmdline->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd[0] < 0)
		perror("fd error");
	dup2(fd[0], STDOUT_FILENO);
	close(fd[0]);
	ft_lstdel_front(&parse->lst_cmdline);
}

void	check_herringbone(t_parsing *parse)
{
	// ft_lstprint_from_head(parse->lst_cmdline);
	// exit(EXIT_FAILURE)
	while ((ft_strchr(parse->lst_cmdline->str, '<') != NULL || ft_strchr(parse->lst_cmdline->str, '>') != NULL) && parse->lst_cmdline)
	{
		// printf("ret = %d \n", ft_lst_strchr_herringbone(parse->lst_cmdline));
		if (ft_strcmp(parse->lst_cmdline->str, "<") == 0)
			input_redirection(parse);
		if (ft_strcmp(parse->lst_cmdline->str, ">") == 0)
			output_redirection(parse);
		// if (ft_strcmp(parse->lst_cmdline->str, "<<") == 0)
		// 	ft_heredoc();
		if (ft_strcmp(parse->lst_cmdline->str, ">>") == 0)
			ft_append(parse);
	}
	// ft_lstprint_from_head(parse->lst_cmdline);
	// exit(EXIT_FAILURE);
}

void execute_cmd(t_parsing *parse)
{
	// 1- watch on redirection
	// 2 execute cmd
	// 3 where ?
	// ft_lstprint_from_head(parse->lst_cmdline);
	// exit(EXIT_FAILURE);
	pid_t child;
	child = fork();
	//char *built_temp;
	if (child < 0)
		perror("fork error\n");
	else if (child == 0)
	{
		parse->built_in_cmd = 0;

		if (ft_strchr(parse->lst_cmdline->str, '<') != NULL
			|| ft_strchr(parse->lst_cmdline->str, '>') != NULL)
			check_herringbone(parse);
		if (check_builtin_input(parse) == 1)
			parsing_cmd(parse);
		else
			parse->built_in_cmd = parsing_built_in(parse);

		// ft_lstprint_from_head(parse->lst_cmdline);
		// exit(EXIT_FAILURE);
		//puts("AA");
		check_herringbone(parse);
		// 	built_temp = parse->lst_cmdline->str;
		// 	// attribuer a une variable la commande builtins. effacer la liste utilisée
		if (ft_lst_strchr_pipe(parse->lst_cmdline) == 0)
			pipex(parse);
		// }
		//int i = 0;
		// while (parse->command[i])
		// {
		// 	printf("cmd[%d] = %s\n", i, parse->command[i]);
		// 	i++;
		// }
		// ft_lstprint_from_head(parse->lst_cmdline);
		//exit(EXIT_FAILURE);
		//printf("BP\n");
		// if (ft_strchr(parse->lst_cmdline->str, '<') != NULL
		// 	&& ft_strchr(parse->lst_cmdline->str, '>') != NULL)
		// if (ft_strchr(parse->lst_cmdline->str, '<') != NULL
		// 	|| ft_strchr(parse->lst_cmdline->str, '>') != NULL)
		//  	check_herringbone(parse);
		if (parse->built_in_cmd > 0)
			execute_built_in(parse);
		// ft_lstprint_from_head(parse->lst_cmdline);
		// exit(EXIT_FAILURE);
		// printf("command = %s\n", parse->command[0]);
		// exit(EXIT_FAILURE);
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

