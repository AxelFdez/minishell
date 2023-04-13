#include "../includes/minishell.h"

void	delete_cmd(t_list **list_cmd)
{
	while (ft_strcmp((*list_cmd)->str, "|") != 0)
				ft_lstdel_front(&(*list_cmd));
			ft_lstdel_front(&(*list_cmd));
}

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
		if (ft_strcmp(parse->lst_cmdline->str, "|") == 0)
			exit(parse->ret_value);
		parse->built_in_cmd = 0;
		if (check_builtin_input(parse) == 1)
			parsing_cmd(parse);
		else
			parse->built_in_cmd = parsing_built_in(parse);
		if (parse->redirection_out == 0)
			dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		if (parse->built_in_cmd > 0)
			execute_built_in(parse);
		execve(parse->command[0], parse->command, parse->env);
		error_exec_message(parse);
		exit(parse->ret_value);
	}
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
		if (parse->redirection_in == 0)
			dup2(pfd[0], STDIN_FILENO);
		close(pfd[0]);
		if (parse->built_in_cmd > 0)
			execute_built_in(parse);
		execve(parse->command[0], parse->command, parse->env);
		error_exec_message(parse);
		exit(parse->ret_value);
	}
	return (child);
}

void	one_pipe(t_parsing *parse)
{
	int		pfd[2];
	int		children[2];

	pipe(pfd);
	children[0] = cmd1(parse, pfd);
	delete_cmd(&parse->lst_cmdline);
	children[1] = cmd2(parse, pfd);
	close(pfd[0]);
	close(pfd[1]);
	for( int i = 1; i >= 0; i--)
	{
		waitpid(children[i],  &parse->status, 0);
		if (i == 1)
			parse->ret_value = parse->status / 256;
	}
}

void	parsing_cmd_in_pipe(t_parsing *parse)
{
	parse->built_in_cmd = 0;
	check_herringbone(parse);
	if (ft_strcmp(parse->lst_cmdline->str, "|") == 0)
			exit(parse->ret_value);
	if (check_builtin_input(parse) == 1)
		parsing_cmd(parse);
	else
		parse->built_in_cmd = parsing_built_in(parse);
}

void	pipe_child(t_parsing *parse, int pfd[2])
{
	close(pfd[0]);
	if (parse->redirection_out == 0)
		dup2(pfd[1], STDOUT_FILENO);
	if (parse->redirection_in == 0)
		dup2(parse->temp_fd, STDIN_FILENO);
	close(parse->temp_fd);
	close(pfd[1]);
	if (parse->built_in_cmd > 0)
		execute_built_in(parse);;
	execve(parse->command[0], parse->command, parse->env);
	error_exec_message(parse);
	exit(parse->ret_value);
}

int	first_cmd(t_parsing *parse)
{
	pid_t	child;
	int		pfd[2];

	pipe(pfd);
	child = fork();
	if (child == -1)
		perror("Fork error");
	else if (child == 0)
	{
		parsing_cmd_in_pipe(parse);
		close(pfd[0]);
		if (parse->redirection_out == 0)
			dup2(pfd[1], STDOUT_FILENO);
		close(parse->temp_fd);
		close(pfd[1]);
		if (parse->built_in_cmd > 0)
			execute_built_in(parse);;
		execve(parse->command[0], parse->command, parse->env);
		error_exec_message(parse);
		exit(parse->ret_value);
	}
	close(pfd[1]);
	parse->temp_fd = pfd[0];
	return (child);
}

int	middle_cmd(t_parsing *parse)
{
	pid_t	child;
	int		pfd[2];

	pipe(pfd);
	child = fork();
	if (child == -1)
		perror("Fork error");
	else if (child == 0)
	{
		parsing_cmd_in_pipe(parse);
		pipe_child(parse, pfd);
	}
	close(pfd[1]);
	close(parse->temp_fd);
	parse->temp_fd = pfd[0];
	return (child);
}

int	last_cmd(t_parsing *parse)
{
		pid_t child;

		child = fork();
		if (child == -1)
		perror("Fork error");
		else if (child == 0)
		{
			check_herringbone(parse);
			parse->built_in_cmd = 0;
			if (parse->redirection_in == 0)
				dup2(parse->temp_fd, STDIN_FILENO);
			close(parse->temp_fd);
			if (check_builtin_input(parse) == 1)
				parsing_cmd(parse);
			else
				parse->built_in_cmd = parsing_built_in(parse);
			if (parse->built_in_cmd > 0)
					execute_built_in(parse);
			execve(parse->command[0], parse->command, parse->env);
			error_exec_message(parse);
			exit(parse->ret_value);
		}
		close(parse->temp_fd);
		return (child);
}

void	pipex(t_parsing *parse)
{
	int		sep;
	int		*children;
	int		i;

	i = 0;
	children = NULL;
	sep = count_pipe(parse->lst_cmdline);
	if (sep == 1)
		one_pipe(parse);
	else
	{
		children = malloc(sizeof(int) * (sep + 1));
		if (!children)
			perror("malloc error");
		children[i] = first_cmd(parse);
		i++;
		delete_cmd(&parse->lst_cmdline);
		while (sep - 1 > 0)
		{
			children[i] = middle_cmd(parse);
			i++;
			sep--;
			delete_cmd(&parse->lst_cmdline);
		}
		children[i] = last_cmd(parse);
		int last_cmd_no = i;
		while (i >= 0)
		{
			waitpid(children[i],  &parse->status, 0);
			if (i == last_cmd_no)
				parse->ret_value = parse->status / 256;
			i--;
		}
		free(children);
		//system("lsof -c minishell");
	}
}
