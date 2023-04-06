#include "../includes/minishell.h"

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
		exit(1);
		// perror("command not found");
	}
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[1]);
	wait(NULL);
	check_herringbone(parse);
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
	parse->last_pipe = 1;
	if (parse->built_in_cmd > 0)
		execute_built_in(parse);
	execve(parse->command[0], parse->command, parse->env);
	exit(1);

	// perror("command not found");
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
		exit(1);
		// perror("command not found");
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
		exit(1);
		// perror("command not found");
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
		exit(1);
		// perror("command not found");
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
	parse->last_pipe = 1;
	if (parse->built_in_cmd > 0)
			execute_built_in(parse);
	execve(parse->command[0], parse->command, parse->env);
	exit(1);
	// perror("command not found");
}

void	pipex(t_parsing *parse)
{
	int		i;
	int		sep;
	int		temp_fd;

	parse->last_pipe = 0;
	sep = count_pipe_until_sep(parse->lst_cmdline);
	if (check_builtin_input(parse) == 1)
		ft_lstdel_front(&parse->lst_cmdline);
	if (sep == 1)
		one_pipe(parse);
	else
	{
		temp_fd = 0;
		temp_fd = first_pipe(parse, temp_fd);
		i = 0;
		while (i < (sep - 2))
		{
			check_herringbone(parse);
			if (check_builtin_input(parse) == 1)
				parsing_cmd(parse);
			else
				parse->built_in_cmd = parsing_built_in(parse);
			if (check_builtin_input(parse) == 1)
				ft_lstdel_front(&parse->lst_cmdline);
			temp_fd = middle_pipe(parse, temp_fd);
			i++;
		}
		check_herringbone(parse);
		if (check_builtin_input(parse) == 1)
			parsing_cmd(parse);
		else
			parse->built_in_cmd = parsing_built_in(parse);
		if (check_builtin_input(parse) == 1)
			ft_lstdel_front(&parse->lst_cmdline);
		last_pipe(parse, temp_fd);
	}
}