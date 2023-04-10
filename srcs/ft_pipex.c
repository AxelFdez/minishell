#include "../includes/minishell.h"

pid_t cmd1(t_parsing *parse, int *pfd)
{
	pid_t child;

	child = fork();
	if (child == -1)
		perror("Fork error");
	else if (child == 0)
	{
		close(pfd[0]);
		check_herringbone(parse);
		parse->built_in_cmd = 0;
		if (check_builtin_input(parse) == 1)
			parsing_cmd(parse);
		else
			parse->built_in_cmd = parsing_built_in(parse);
		if (parse->built_in_cmd > 0)
			execute_built_in(parse);
		//if (parse->redirection_out == 0)
		dup2(pfd[1], STDOUT_FILENO);
		dprintf(2, "cmd = %s\n", parse->command[0]);
		execve(parse->command[0], parse->command, parse->env);
		error_exec_message(parse);
	}
	ft_lstdel_front(&parse->lst_cmdline);
	ft_lstdel_front(&parse->lst_cmdline);
	return child;
}

pid_t cmd2(t_parsing *parse, int *pfd)
{
	pid_t child;

	child = fork();
	if (child == -1)
		perror("Fork error");
	else if (child == 0)
	{
		close(pfd[1]);
		check_herringbone(parse);
		parse->built_in_cmd = 0;
		if (check_builtin_input(parse) == 1)
			parsing_cmd(parse);
		else
			parse->built_in_cmd = parsing_built_in(parse);
		if (parse->built_in_cmd > 0)
			execute_built_in(parse);
		dup2(pfd[0], STDIN_FILENO);
		//if (parse->redirection_out == 0)
		dprintf(2, "cmd 2 = %s\n", parse->command[0]);
		execve(parse->command[0], parse->command, parse->env);
		error_exec_message(parse);
	}
	ft_lstdel_front(&parse->lst_cmdline);
	return (child);
}

void	one_pipe(t_parsing *parse)
{
	int		pfd[2];
	int		children[2];

	pipe(pfd);
	while (parse->lst_cmdline)
	{
		children[0] = cmd1(parse, pfd);
		children[1] = cmd2(parse, pfd);
		close(pfd[0]);
		close(pfd[1]);
		for( int i = 1; i >= 0; i--)
		{
			waitpid(children[i], 0, 0);
		}
	}
	//waitpid(children[0], 0, 0);
}

// void	one_pipe(t_parsing *parse)
// {
// 	pid_t	child;
// 	int		pfd[2];

// 	pipe(pfd);
// 	child = fork();
// 	if (child == -1)
// 		perror("Fork error");
// 	else if (child == 0)
// 		pipe_child(parse, pfd, 0, 0);
// 	else
// 	{
// 		close(pfd[1]);
// 		dup2(pfd[0], STDIN_FILENO);
// 		dup2(parse->fd_stdout, STDOUT_FILENO);
// 		close(pfd[0]);
// 		waitpid(child, 0, 0);
// 		check_herringbone(parse);
// 		del_parsed_cmd(parse);
// 		if (check_builtin_input(parse) == 1)
// 				parsing_cmd(parse);
// 		else
// 			parse->built_in_cmd = parsing_built_in(parse);
// 		if (parse->built_in_cmd > 0)
// 			execute_built_in(parse);
// 		execve(parse->command[0], parse->command, parse->env);
// 		error_exec_message(parse);
// 	}
// }

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
	waitpid(child, 0, 0);
	dup2(pfd[0], STDIN_FILENO);
	close(pipe_temp);
	close(pfd[1]);
	dup2(parse->fd_stdout, STDOUT_FILENO);
	del_parsed_cmd(parse);
	check_herringbone(parse);
	if (check_builtin_input(parse) == 1)
		parsing_cmd(parse);
	else
		parse->built_in_cmd = parsing_built_in(parse);
	if (parse->built_in_cmd > 0)
			execute_built_in(parse);
	execve(parse->command[0], parse->command, parse->env);
	error_exec_message(parse);
}

void	parsing_cmd_in_pipe(t_parsing *parse)
{
	check_herringbone(parse);
	if (check_builtin_input(parse) == 1)
		parsing_cmd(parse);
	else
		parse->built_in_cmd = parsing_built_in(parse);
	if (check_builtin_input(parse) == 1)
		ft_lstdel_front(&parse->lst_cmdline);
}

void	pipex(t_parsing *parse)
{
	int		sep;
	//int		temp_fd;

	sep = count_pipe(parse->lst_cmdline);
	// printf("sep = %d\n", sep);
	// print_list(parse->lst_cmdline);
	// exit(EXIT_FAILURE);
	// if (check_builtin_input(parse) == 1)
		//ft_lstdel_front(&parse->lst_cmdline);
	if (sep == 1)
		one_pipe(parse);
	// temp_fd = 0;
	// temp_fd = first_pipe(parse, temp_fd);
	// while (sep - 2 > 0)
	// {
	// 	parsing_cmd_in_pipe(parse);
	// 	temp_fd = middle_pipe(parse, temp_fd);
	// 	sep--;
	// }
	// parsing_cmd_in_pipe(parse);
	// last_pipe(parse, temp_fd);
}

// void	pipex(t_parsing *parse)
// {
// 	int		sep;
// 	int		temp_fd;

// 	sep = count_pipe(parse->lst_cmdline);
// 	if (check_builtin_input(parse) == 1)
// 		ft_lstdel_front(&parse->lst_cmdline);
// 	if (sep == 1)
// 		one_pipe(parse);
// 	temp_fd = 0;
// 	temp_fd = first_pipe(parse, temp_fd);
// 	while (sep - 2 > 0)
// 	{
// 		parsing_cmd_in_pipe(parse);
// 		temp_fd = middle_pipe(parse, temp_fd);
// 		sep--;
// 	}
// 	parsing_cmd_in_pipe(parse);
// 	last_pipe(parse, temp_fd);
// }