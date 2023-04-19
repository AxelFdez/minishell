
#include "../includes/minishell.h"

void	parsing_command_child(t_parsing *parse)
{
	parse->built_in_cmd = 0;
	check_herringbone(parse);
	if (!parse->lst_cmdline || ft_strcmp(parse->lst_cmdline->str, "|") == 0)
		exit(sig.return_value);
	if (check_builtin_input(parse) == 1)
		parsing_cmd(parse);
	else
		parse->built_in_cmd = parsing_built_in(parse);
	if (parse->heredoc_pfd > 0)
	{
		dup2(parse->heredoc_pfd, STDIN_FILENO);
		close(parse->heredoc_pfd);
	}
}

void	execute_command_child(t_parsing *parse)
{
	if (parse->built_in_cmd > 0)
		execute_built_in(parse);
	execve(parse->command[0], parse->command, parse->env);
	error_exec_message(parse);
	exit(sig.return_value);
}

void	command_father(t_parsing *parse)
{
	if (WIFEXITED(parse->status))
		sig.return_value = WEXITSTATUS(parse->status);
	else if (WIFSIGNALED(parse->status))
	{
		sig.return_value = WTERMSIG(parse->status);
		if (sig.return_value == 2)
			sig.return_value = 130;
		else if (sig.return_value == 3)
			sig.return_value = 131;
		else if (sig.return_value == 11)
			sig.return_value = 127;
	}
	if (parse->heredoc_pfd > 0)
	{
		close(parse->heredoc_pfd);
		dup2(parse->fd_stdin, STDIN_FILENO);
		parse->heredoc_pfd = 0;
	}
}

static void	simple_command(t_parsing *parse)
{
	pid_t child;

	parse->status = 0;
	check_heredoc(parse);
	if (!parse->lst_cmdline)
		return;
	sig.child = 0;
	child = fork();
	if (child < 0)
		perror("fork error\n");
	else if (child == 0)
	{
		parsing_command_child(parse);
		execute_command_child(parse);
	}
	waitpid(child, &parse->status, 0);
	command_father(parse);
}

void execute_cmd(t_parsing *parse)
{
	sig.heredoc = 0;
	built_in_used_alone(parse);
	if (!parse->lst_cmdline)
		return ;
	sig.return_value = 0;
	if (ft_lst_strchr_pipe(parse->lst_cmdline) == 0)
		pipex(parse);
	else
		simple_command(parse);
	return;
}
