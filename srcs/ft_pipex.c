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

	check_heredoc(parse);
	child = fork();
	if (child == -1)
		perror("Fork error");
	else if (child == 0)
	{
		close(pfd[0]);
		check_herringbone(parse);
		if (!parse->lst_cmdline || ft_strcmp(parse->lst_cmdline->str, "|") == 0)
			exit(sig.return_value);
		// if (ft_strcmp(parse->lst_cmdline->str, "|") == 0)
		// 	exit(parse->ret_value);
		parse->built_in_cmd = 0;
		if (check_builtin_input(parse) == 1)
			parsing_cmd(parse);
		else
			parse->built_in_cmd = parsing_built_in(parse);
		if (parse->heredoc_pfd > 0)
		{
			dup2(parse->heredoc_pfd, STDIN_FILENO);
			close(parse->heredoc_pfd);
		}
		if (parse->redirection_out == 0)
			dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		if (parse->built_in_cmd > 0)
			execute_built_in(parse);
		execve(parse->command[0], parse->command, parse->env);
		error_exec_message(parse);
		exit(sig.return_value);
	}
	if (parse->heredoc_pfd > 0)
	{
		close(parse->heredoc_pfd);
		dup2(parse->fd_stdin, STDIN_FILENO);
		parse->heredoc_pfd = 0;
	}
	return child;
}

pid_t cmd2(t_parsing *parse, int *pfd)
{
	pid_t child;

	check_heredoc(parse);
	if (!parse->lst_cmdline)
		return (-1);
	child = fork();
	if (child == -1)
		perror("Fork error");
	else if (child == 0)
	{
		close(pfd[1]);
		check_herringbone(parse);
		if (!parse->lst_cmdline)
			exit(sig.return_value);
		parse->built_in_cmd = 0;
		if (check_builtin_input(parse) == 1)
			parsing_cmd(parse);
		else
			parse->built_in_cmd = parsing_built_in(parse);
		if (parse->redirection_in == 0)
			dup2(pfd[0], STDIN_FILENO);
		if (parse->heredoc_pfd > 0)
		{
			dup2(parse->heredoc_pfd, STDIN_FILENO);
			close(parse->heredoc_pfd);
		}
		close(pfd[0]);
		if (parse->built_in_cmd > 0)
			execute_built_in(parse);
		execve(parse->command[0], parse->command, parse->env);
		error_exec_message(parse);
		exit(sig.return_value);
	}
	if (parse->heredoc_pfd > 0)
	{
		close(parse->heredoc_pfd);
		dup2(parse->fd_stdin, STDIN_FILENO);
	}
	return (child);
}

void	one_pipe(t_parsing *parse)
{
	int		pfd[2];
	int		children[2];
	int		last_cmd_value_return;

	last_cmd_value_return = 0;
	pipe(pfd);
	children[0] = cmd1(parse, pfd);
	delete_cmd(&parse->lst_cmdline);
	children[1] = cmd2(parse, pfd);
	close(pfd[0]);
	close(pfd[1]);
	for( int i = 1; i >= 0; i--)
	{
		waitpid(children[i],  &sig.return_value, 0);
		if (i == 1)
			last_cmd_value_return = sig.return_value / 256;
	}
	sig.return_value = last_cmd_value_return;
}

void	parsing_cmd_in_pipe(t_parsing *parse)
{
	parse->built_in_cmd = 0;
	check_herringbone(parse);
	if (!parse->lst_cmdline || ft_strcmp(parse->lst_cmdline->str, "|") == 0)
			exit(sig.return_value);
	// if (ft_strcmp(parse->lst_cmdline->str, "|") == 0)
	// 		exit(parse->ret_value);
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
	if (parse->heredoc_pfd > 0)
		{
			dup2(parse->heredoc_pfd, STDIN_FILENO);
			close(parse->heredoc_pfd);
		}
	close(parse->temp_fd);
	close(pfd[1]);
	if (parse->built_in_cmd > 0)
		execute_built_in(parse);;
	execve(parse->command[0], parse->command, parse->env);
	error_exec_message(parse);
	exit(sig.return_value);
}

int	first_cmd(t_parsing *parse)
{
	pid_t	child;
	int		pfd[2];

	check_heredoc(parse);
	if (!parse->lst_cmdline)
		return (-1);
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
		if (parse->heredoc_pfd > 0)
		{
			dup2(parse->heredoc_pfd, STDIN_FILENO);
			close(parse->heredoc_pfd);
		}
		close(parse->temp_fd);
		close(pfd[1]);
		if (parse->built_in_cmd > 0)
			execute_built_in(parse);;
		execve(parse->command[0], parse->command, parse->env);
		error_exec_message(parse);
		exit(sig.return_value);
	}
	close(pfd[1]);
	parse->temp_fd = pfd[0];
	return (child);
}

int	middle_cmd(t_parsing *parse)
{
	pid_t	child;
	int		pfd[2];

	check_heredoc(parse);
	if (!parse->lst_cmdline)
		return (-1);
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

		check_heredoc(parse);
		if (!parse->lst_cmdline)
		return (-1);
		child = fork();
		if (child == -1)
		perror("Fork error");
		else if (child == 0)
		{
			check_herringbone(parse);
			if (!parse->lst_cmdline)
				exit(sig.return_value);
			parse->built_in_cmd = 0;
			if (parse->redirection_in == 0)
				dup2(parse->temp_fd, STDIN_FILENO);
			if (parse->heredoc_pfd > 0)
			{
				dup2(parse->heredoc_pfd, STDIN_FILENO);
				close(parse->heredoc_pfd);
			}
			close(parse->temp_fd);
			if (check_builtin_input(parse) == 1)
				parsing_cmd(parse);
			else
				parse->built_in_cmd = parsing_built_in(parse);
			if (parse->built_in_cmd > 0)
					execute_built_in(parse);
			execve(parse->command[0], parse->command, parse->env);
			error_exec_message(parse);
			exit(sig.return_value);
		}
		close(parse->temp_fd);
		if (parse->heredoc_pfd > 0)
		{
			close(parse->heredoc_pfd);
			dup2(parse->fd_stdin, STDIN_FILENO);
		}
		return (child);
}

void	pipex(t_parsing *parse)
{
	int		sep;
	int		*children;
	int		i;
	int		last_cmd_value_return;

	i = 0;
	children = NULL;
	last_cmd_value_return = 0;
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
			waitpid(children[i],  &sig.return_value, 0);
			if (i == last_cmd_no)
				last_cmd_value_return = sig.return_value / 256;
			i--;
		}
		free(children);
		sig.return_value = last_cmd_value_return;
		//system("lsof -c minishell");
	}
}
