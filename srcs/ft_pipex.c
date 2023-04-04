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
		pipe_child(parse, pfd, 0, 0);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[1]);
	wait(&child);
	check_herringbone(parse);
	// print_list(parse->lst_cmdline);
	del_parsed_cmd(parse);
	if (check_builtin_input(parse) == 1)
			parsing_cmd(parse);
	else
		parse->built_in_cmd = parsing_built_in(parse);
	parse->last_pipe = 1;
	if (parse->built_in_cmd > 0)
		execute_built_in(parse);
	execve(parse->command[0], parse->command, parse->env);
	// printf("minishell: ");
	// perror(parse->command[0]);
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
		pipe_child(parse, pfd, 0, 0);
	del_parsed_cmd(parse);
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
		pipe_child(parse, pfd, pipe_temp, 2);
	if (parse->built_in_cmd > 0)
	del_parsed_cmd(parse);
	close(pipe_temp);
	pipe_temp = pfd[0];
	close(pfd[1]);
	return (pipe_temp);
}

void	last_pipe(t_parsing *parse, int pipe_temp)
{
	pid_t	child;
	int		pfd[2];

	pipe(pfd);
	child = fork();
	if (child == -1)
		perror("Fork error");
	else if (child == 0)
		pipe_child(parse, pfd, pipe_temp, 2);
	dup2(pfd[0], STDIN_FILENO);
	close(pipe_temp);
	close(pfd[1]);
	del_parsed_cmd(parse);
	if (check_builtin_input(parse) == 1)
		parsing_cmd(parse);
	else
		parse->built_in_cmd = parsing_built_in(parse);
	parse->last_pipe = 1;
	if (parse->built_in_cmd > 0)
			execute_built_in(parse);
	execve(parse->command[0], parse->command, parse->env);
	// perror("command not found");
}

void	pipex(t_parsing *parse)
{
	int		sep;
	int		temp_fd;

	parse->last_pipe = 0;
	sep = count_pipe_until_sep(parse->lst_cmdline);
	if (check_builtin_input(parse) == 1)
		ft_lstdel_front(&parse->lst_cmdline);
	// print_list(parse->lst_cmdline);
	// exit(EXIT_FAILURE);
	if (sep == 1)
		one_pipe(parse);
	temp_fd = 0;
	temp_fd = first_pipe(parse, temp_fd);
	while (sep - 2 > 0)
	{
		check_herringbone(parse);
		if (check_builtin_input(parse) == 1)
			parsing_cmd(parse);
		else
			parse->built_in_cmd = parsing_built_in(parse);
		if (check_builtin_input(parse) == 1)
			ft_lstdel_front(&parse->lst_cmdline);
		temp_fd = middle_pipe(parse, temp_fd);
		sep--;
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