#include "../includes/minishell.h"

void	one_pipe(t_parsing *parse)
{
	pid_t	child;
	int		pfd[2];

	printf ("TEST\n");
	pipe(pfd);
	child = fork();
	if (child == -1)
		perror("Fork error");
	else if (child == 0)
	{
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		execute_built_in(parse);
	// printf("cmd-fils = %s\n", parse->lst_cmdline->str);
		execve(parse->command[0], parse->command, parse->env);
		perror("command not found");
	}
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[1]);
	wait(NULL);
	printf("pere = %s\n", parse->lst_cmdline->str);
	printf("nb = %d\n", check_builtin_input(parse));
	if (check_builtin_input(parse) == 1)
			parsing_cmd(parse);
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
		execute_built_in(parse);
		execve(parse->command[0], parse->command, parse->env);
		perror("command not found");
	}
	wait(NULL);
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
		execute_built_in(parse);
		execve(parse->command[0], parse->command, parse->env);
		perror("command not found");
	}
	wait(NULL);
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
		execute_built_in(parse);
		execve(parse->command[0], parse->command, parse->env);
		perror("command not found");
	}
	dup2(pfd[0], STDIN_FILENO);
	close(temp_fd);
	close(pfd[1]);
	if (check_builtin_input(parse) == 1)
			parsing_cmd(parse);
	wait(NULL);
	execute_built_in(parse);
	execve(parse->command[0], parse->command, parse->env);
	perror("command not found");
}

void	pipex(t_parsing *parse)
{
	int		i;
	int		sep;
	int		temp_fd;
	if (check_builtin_input(parse) == 1)
		ft_lstdel_front(&parse->lst_cmdline);
	//printf("path fils = %s\n", parse->lst_cmdline->str);
	//ft_lstprint_from_head(parse->lst_cmdline->next);
	// compter le nombre de pipe jusqu'a un separateur / fin
	//printf("num = %d\n", ft_lst_strchr_meta(parse->lst_cmdline->next));
	if (ft_lst_strchr_meta(parse->lst_cmdline) == 1 || (ft_lst_strchr_meta(parse->lst_cmdline->next) == 0 && check_builtin_input(parse) == 0))
		one_pipe(parse);
	else
	{
	// iterrer de i jusqu-a nb pipe
		//printf("count pipe = %d\n", count_pipe_until_sep(parse->lst_cmdline));
		temp_fd = 0;
		temp_fd = first_pipe(parse, temp_fd);
		i = 0;
		sep = count_pipe_until_sep(parse->lst_cmdline);
		//printf ("sep = %d", sep);
		while (i < (sep - 1))
		{
			if (check_builtin_input(parse) == 1)
			parsing_cmd(parse);
			ft_lstdel_front(&parse->lst_cmdline);
			temp_fd = middle_pipe(parse, temp_fd);
			i++;
		}
			if (check_builtin_input(parse) == 1)
			parsing_cmd(parse);
			ft_lstdel_front(&parse->lst_cmdline);
			// ft_lstprint_from_head(parse->lst_cmdline);
			// exit(EXIT_SUCCESS);
			last_pipe(parse, temp_fd);
	}
}