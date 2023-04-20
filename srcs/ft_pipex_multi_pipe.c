/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_multi_pipe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axfernan <axfernan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:58:07 by axfernan          #+#    #+#             */
/*   Updated: 2023/04/20 11:31:38 by axfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	redirections_in_middle_cmd(t_parsing *parse, int pfd[2])
{
	if (parse->redirection_out == 0)
		dup2(pfd[1], STDOUT_FILENO);
	if (parse->redirection_in == 0 && parse->heredoc_pfd == 0)
		dup2(parse->temp_fd, STDIN_FILENO);
}

static int	first_cmd(t_parsing *parse)
{
	pid_t	child;
	int		pfd[2];

	check_heredoc(parse);
	if (!parse->lst_cmdline)
		return (-1);
	g_sig.child = 0;
	pipe(pfd);
	child = fork();
	if (child == -1)
		perror("Fork error");
	else if (child == 0)
	{
		parsing_command_child(parse);
		close(pfd[0]);
		if (parse->redirection_out == 0)
			dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
		execute_command_child(parse);
	}
	close(pfd[1]);
	parse->temp_fd = pfd[0];
	return (child);
}

static int	middle_cmd(t_parsing *parse)
{
	pid_t	child;
	int		pfd[2];

	check_heredoc(parse);
	if (!parse->lst_cmdline)
		return (-1);
	g_sig.child = 0;
	pipe(pfd);
	child = fork();
	if (child == -1)
		perror("Fork error");
	else if (child == 0)
	{
		parsing_command_child(parse);
		close(pfd[0]);
		redirections_in_middle_cmd(parse, pfd);
		close(parse->temp_fd);
		close(pfd[1]);
		execute_command_child(parse);
	}
	close(pfd[1]);
	close(parse->temp_fd);
	parse->temp_fd = pfd[0];
	return (child);
}

static int	last_cmd(t_parsing *parse)
{
	pid_t	child;

	check_heredoc(parse);
	if (!parse->lst_cmdline)
		return (-1);
	g_sig.child = 0;
	child = fork();
	if (child == -1)
		perror("Fork error");
	else if (child == 0)
	{
		parsing_command_child(parse);
		if (parse->redirection_in == 0)
			dup2(parse->temp_fd, STDIN_FILENO);
		close(parse->temp_fd);
		execute_command_child(parse);
	}
	close(parse->temp_fd);
	command_father(parse);
	return (child);
}

void	multi_pipes(t_parsing *parse, t_pipex *pipex)
{
	pipex->children = malloc(sizeof(int) * (pipex->sep + 1));
	if (!pipex->children)
		perror("malloc error");
	pipex->children[pipex->i] = first_cmd(parse);
	pipex->i++;
	delete_cmd(&parse->lst_cmdline);
	while (pipex->sep - 1 > 0)
	{
		pipex->children[pipex->i] = middle_cmd(parse);
		pipex->i++;
		pipex->sep--;
		delete_cmd(&parse->lst_cmdline);
	}
	pipex->children[pipex->i] = last_cmd(parse);
	pipex->last_cmd_no = pipex->i;
	while (pipex->i >= 0)
	{
		waitpid(pipex->children[pipex->i], &g_sig.return_value, 0);
		if (pipex->i == pipex->last_cmd_no)
			pipex->last_cmd_value_return = g_sig.return_value / 256;
		pipex->i--;
	}
	free(pipex->children);
	g_sig.return_value = pipex->last_cmd_value_return;
}
