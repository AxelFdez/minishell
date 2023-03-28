

#include "../includes/minishell.h"

static char	**find_path_in_env(t_parsing *parse)
{
	int		i;
	char	*path;
	char	**split;

	i = 0;
	while (ft_strstr(parse->env[i], "PATH") == NULL)
		i++;
	path = parse->env[i];
	path = ft_strtrim(path, "PATH=");
	split = ft_split(path, ':');
	free(path);
	i = 0;
	while (split[i])
	{
		split[i] = ft_strjoin_free_s1(split[i], "/");
		split[i] = ft_strjoin_free_s1(split[i], parse->command[0]);
		i++;
	}
	return (split);
}

char	*path_of_command(t_parsing *parse)
{
	int		i;
	int		j;
	char	**split;

	split = find_path_in_env(parse);
	i = 0;
	while (access(split[i], F_OK) != 0)
	{
		i++;
		if (split[i] == 0)
		{
			perror("command not found");
			j = 0;
			while (j < i)
			{
				free(split[j]);
				j++;
			}
			free(split);
			return (NULL);
		}
	}
	return (split[i]);
}

void	cmd_lst_to_tab(t_parsing *parse)
{
	int		i;
	t_list *temp;
	t_list *temp2;

	temp = parse->lst_cmdline;
	temp2 = parse->lst_cmdline;
	i = 0;
	while (temp && ft_strchr(temp->str, '|') == NULL
		&& ft_strchr(temp->str, '<') == NULL
		&& ft_strchr(temp->str, '>') == NULL)
	{
		i++;
		temp = temp->next;
	}
	parse->command = NULL;
	parse->command = malloc(sizeof(char *) * (i + 1));
	if (!parse->command)
		perror("error malloc");
	i = 0;
	parse->lst_target = 0;
	while (temp2 && ft_strchr(temp2->str, '|') == NULL
		&& ft_strchr(temp2->str, '<') == NULL
		&& ft_strchr(temp2->str, '>') == NULL)
	{
		parse->command[i] = ft_strdup(temp2->str);
		i++;
		parse->lst_target++;
		temp2 = temp2->next;
	}
	parse->command[i] = 0;
}

void	parsing_cmd(t_parsing *parse)
{
	int i;

	i = 0;
	cmd_lst_to_tab(parse);
	if (access(parse->command[0], F_OK))
		parse->command[0] = path_of_command(parse);
	while (i < parse->lst_target)
	{
		ft_lstdel_front(&parse->lst_cmdline);
		i++;
	}
		// ft_lstprint_from_head(parse->lst_cmdline);
		// exit(EXIT_FAILURE);
	//printf("ret = %d\n", parse->lst_target);
}

int	count_pipe_until_sep(t_list *list)
{
	t_list	*temp;
	int		count;

	count = 0;
	temp = list;
	while (temp)
	{
		if (temp->str[0] == '|')
			count++;
		if (temp->str[0] == '<' && temp->str[0] == '>')
		{
			return (count);
		}
		temp = temp->next;
	}
	return (count);
}

void	one_pipe(t_parsing *parse)
{
	pid_t	child;
	int		pfd[2];

	pipe(pfd);
	child = fork();
	if (child == -1)
		perror("Fork error");
	else if (child == 0)
	{
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[0]);
		if (parse->built_in_cmd > 0)
			execute_built_in(parse);;
		execve(parse->command[0], parse->command, parse->env);
		perror("command not found");
	}
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[1]);
	wait(NULL);
	if (parse->built_in_cmd > 0)
	{
		int i = 0;
		while (i < parse->lst_target + 1)
		{
			parse->built_in_cmd = 0;
			ft_lstdel_front(&parse->lst_cmdline);
			i++;
		}
	}
	if (check_builtin_input(parse) == 1)
			parsing_cmd(parse);
	else
		parse->built_in_cmd = parsing_built_in(parse);
	if (parse->built_in_cmd > 0)
		execute_built_in(parse);
	execve(parse->command[0], parse->command, parse->env);
	perror("command not found");
}

int	first_pipe(t_parsing *parse, int temp_fd)
{
	pid_t	child;
	int		pfd[2];

	pipe(pfd);
	child = fork();
	if (child == -1)
		perror("Fork error");
	else if (child == 0)
	{
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[0]);
		if (parse->built_in_cmd > 0)
			execute_built_in(parse);
		execve(parse->command[0], parse->command, parse->env);
		perror("command not found");
	}
	wait(NULL);
	if (parse->built_in_cmd > 0)
	{
		int i = 0;
		while (i < parse->lst_target + 1)
		{
			parse->built_in_cmd = 0;
			ft_lstdel_front(&parse->lst_cmdline);
			i++;
		}
	}
	temp_fd = pfd[0];
	close(pfd[1]);
	return (temp_fd);
}

int	middle_pipe(t_parsing *parse, int pipe_temp)
{
	pid_t	child;
	int		pfd[2];

	pipe(pfd);
	child = fork();
	if (child == -1)
		perror("Fork error");
	else if (child == 0)
	{
		dup2(pipe_temp, STDIN_FILENO);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[0]);
		if (parse->built_in_cmd > 0)
			execute_built_in(parse);
		execve(parse->command[0], parse->command, parse->env);
		perror("command not found");
	}
	wait(NULL);
	if (parse->built_in_cmd > 0)
	{
		int i = 0;
		while (i < parse->lst_target + 1)
		{
			parse->built_in_cmd = 0;
			ft_lstdel_front(&parse->lst_cmdline);
			i++;
		}
	}
	close(pipe_temp);
	pipe_temp = pfd[0];
	close(pfd[1]);
	return (pipe_temp);
}

void	last_pipe(t_parsing *parse, int temp_fd)
{
	pid_t	child;
	int		pfd[2];

	pipe(pfd);
	child = fork();
	if (child == -1)
		perror("Fork error");
	else if (child == 0)
	{
		dup2(temp_fd, STDIN_FILENO);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[0]);
		if (parse->built_in_cmd > 0)
			execute_built_in(parse);
		execve(parse->command[0], parse->command, parse->env);
		perror("command not found");
	}
	dup2(pfd[0], STDIN_FILENO);
	close(temp_fd);
	close(pfd[1]);
	wait(NULL);
	if (parse->built_in_cmd > 0)
	{
		int i = 0;
		while (i < parse->lst_target + 1)
		{
			parse->built_in_cmd = 0;
			ft_lstdel_front(&parse->lst_cmdline);
			i++;
		}
	}
	if (check_builtin_input(parse) == 1)
		parsing_cmd(parse);
	else
		parse->built_in_cmd = parsing_built_in(parse);
	if (parse->built_in_cmd > 0)
			execute_built_in(parse);
	execve(parse->command[0], parse->command, parse->env);
	perror("command not found");
}

void	pipex(t_parsing *parse)
{
	int		i;
	int		sep;
	int		temp_fd;
	//printf ("1  = %s\n", parse->lst_cmdline->str);
	sep = count_pipe_until_sep(parse->lst_cmdline);
	if (check_builtin_input(parse) == 1)
		ft_lstdel_front(&parse->lst_cmdline);
	//printf("path fils = %s\n", parse->lst_cmdline->str);
	//ft_lstprint_from_head(parse->lst_cmdline->next);
	// compter le nombre de pipe jusqu'a un separateur / fin
	//printf("num = %d\n", ft_lst_strchr_meta(parse->lst_cmdline->next));
	if (sep == 1)
		one_pipe(parse);
	else
	{
	// iterrer de i jusqu-a nb pipe
		//printf("count pipe = %d\n", count_pipe_until_sep(parse->lst_cmdline));
		temp_fd = 0;
		temp_fd = first_pipe(parse, temp_fd);
		i = 0;
		while (i < (sep - 2))
		{
			if (check_builtin_input(parse) == 1)
				parsing_cmd(parse);
			else
				parse->built_in_cmd = parsing_built_in(parse);
			if (check_builtin_input(parse) == 1)
				ft_lstdel_front(&parse->lst_cmdline);
			temp_fd = middle_pipe(parse, temp_fd);
			i++;
		}
		if (check_builtin_input(parse) == 1)
			parsing_cmd(parse);
		else
			parse->built_in_cmd = parsing_built_in(parse);
		if (check_builtin_input(parse) == 1)
			ft_lstdel_front(&parse->lst_cmdline);
		last_pipe(parse, temp_fd);
	}
}

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
		check_herringbone(parse);
		if (check_builtin_input(parse) == 1)
			parsing_cmd(parse);
		else
			parse->built_in_cmd = parsing_built_in(parse);

		// ft_lstprint_from_head(parse->lst_cmdline);
		// exit(EXIT_FAILURE);
		//puts("AA");
		//check_herringbone(parse);
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
			if (parse.lst_cmdline)
			{
				execute_cmd(&parse);
				ft_lstdel_all(&parse.lst_cmdline);
			}
			//system("leaks minishell");
		}
	}
	puts("end");
	system("leaks minishell");
	return (0);
}