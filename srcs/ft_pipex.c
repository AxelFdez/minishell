/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axfernan <axfernan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:09:01 by axfernan          #+#    #+#             */
/*   Updated: 2023/04/20 11:18:52 by axfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	cmd1(t_parsing *parse, int *pfd)
{
	pid_t	child;

	check_heredoc(parse);
	g_sig.child = 0;
	child = fork();
	if (child == -1)
		perror("Fork error");
	else if (child == 0)
	{
		close(pfd[0]);
		parsing_command_child(parse);
		if (parse->redirection_out == 0)
			dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		execute_command_child(parse);
	}
	command_father(parse);
	return (child);
}

pid_t	cmd2(t_parsing *parse, int *pfd)
{
	pid_t	child;

	check_heredoc(parse);
	g_sig.child = 0;
	if (!parse->lst_cmdline)
		return (-1);
	child = fork();
	if (child == -1)
		perror("Fork error");
	else if (child == 0)
	{
		close(pfd[1]);
		parsing_command_child(parse);
		if (parse->redirection_in == 0)
			dup2(pfd[0], STDIN_FILENO);
		close(pfd[0]);
		execute_command_child(parse);
	}
	command_father(parse);
	return (child);
}

void	one_pipe(t_parsing *parse)
{
	int		pfd[2];
	int		children[2];
	int		last_cmd_value_return;
	int		i;

	last_cmd_value_return = 0;
	pipe(pfd);
	children[0] = cmd1(parse, pfd);
	delete_cmd(&parse->lst_cmdline);
	children[1] = cmd2(parse, pfd);
	close(pfd[0]);
	close(pfd[1]);
	i = 1;
	while (i >= 0)
	{
		waitpid(children[i], &g_sig.return_value, 0);
		if (i == 1)
			last_cmd_value_return = g_sig.return_value / 256;
		i--;
	}
	g_sig.return_value = last_cmd_value_return;
}

void	pipex(t_parsing *parse)
{
	t_pipex	pipex;

	pipex.children = NULL;
	pipex.i = 0;
	pipex.last_cmd_value_return = 0;
	pipex.last_cmd_no = 0;
	pipex.sep = count_pipe(parse->lst_cmdline);
	if (pipex.sep == 1)
		one_pipe(parse);
	else
		multi_pipes(parse, &pipex);
}
