
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
	while (temp && ft_strchr(temp->str, '|') == NULL) //jusqu-a un meta-caractere
	{
		i++;
		temp = temp->next;
	}
	parse->command = NULL;
	parse->command = malloc(sizeof(char *) * (i + 1));
	if (!parse->command)
		perror("error malloc");
	i = 0;
	while (temp2 && ft_strchr(temp2->str, '|') == NULL)
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
}

void is_pipe_out(t_parsing *parse, int first_middle_or_last_pipe, int which_pfd)
{
	pipe(parse->pfd);
	if (first_middle_or_last_pipe == 0 && which_pfd == 0)
	{
		dup2(parse->pfd[1], STDOUT_FILENO);
		close(parse->pfd[0]);
		first_middle_or_last_pipe++;
	}
	else if (first_middle_or_last_pipe == 1 && which_pfd == 0)
	{
		dup2(parse->pfd[0], STDIN_FILENO);
		dup2(parse->pfd[1], STDOUT_FILENO);
		close(parse->pfd[0]);
		close(parse->pfd[1]);
	}
	else if (first_middle_or_last_pipe == 1 && which_pfd == 1)
	{
		dup2(parse->pfd[0], STDIN_FILENO);
		dup2(parse->pfd[1], STDOUT_FILENO);
		close(parse->pfd[0]);
		close(parse->pfd[1]);
	}
	else if (first_middle_or_last_pipe == 2)
	{
		dup2(parse->pfd[0], STDIN_FILENO);
		close(parse->pfd[0]);
		close(parse->pfd[1]);
	}
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
		close(pfd[1]);
		execve(parse->command[0], parse->command, parse->env);
		perror("command not found");
	}
	parsing_cmd(parse);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[1]);
	wait(NULL);
	execve(parse->command[0], parse->command, parse->env);
	perror("command not found");
}

void	pipex(t_parsing *parse)
{
	// int		i;
	// int		temp_fd;
	ft_lstdel_front(&parse->lst_cmdline);
	// compter le nombre de pipe jusqu'a un separateur / fin
	one_pipe(parse);
	// iterrer de i jusqu-a nb pipe
	// temp_fd = 0;

	// temp_fd = first_pipe(temp_fd, argv, env);
	// i = 3;
	// while (i < argc - 3)
	// {
	// 	temp_fd = middle_pipe(i, temp_fd, argv, env);
	// 	i++;
	// }
	// 	last_pipe(argc, temp_fd, argv, env);
}

void execute_cmd(t_parsing *parse)
{
	//ignore meta_characters (delete meta char when executed ?)
	// 1- watch on redirection
	// 2 execute cmd
	// 3 where ?

	pid_t child;
	child = fork();
	if (child < 0)
		perror("fork error\n");
	else if (child == 0)
	{
		parsing_cmd(parse);
		// ft_lstprint_from_head(parse->lst_cmdline);
		// if (parse->lst_cmdline->str[0] == '|')
		// 	pipex(parse);
		//printf("path = %s\n", parse->command[0]);
		// exit(EXIT_FAILURE);
	// 	int i = 0;
	// while (parse->command[i])
	// {
	// 	printf("cmd[%d] = %s\n", i, parse->command[i]);
	// 	i++;
	// }
	// ft_lstprint_from_head(parse->lst_cmdline);
	//  exit(EXIT_FAILURE);
		execve(parse->command[0], parse->command, parse->env);
		perror("command not found");
	}
	wait(NULL);
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

