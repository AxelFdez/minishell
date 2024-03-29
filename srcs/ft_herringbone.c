/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herringbone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axfernan <axfernan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:50:00 by axfernan          #+#    #+#             */
/*   Updated: 2023/12/13 10:22:17 by axfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	input_redirection(t_list **parse)
{
	int fd;
	ft_lstdel_current(&(*parse));
	fd = open((*parse)->str, O_RDONLY);
	if (access((*parse)->str, F_OK) != 0 || access((*parse)->str, R_OK) != 0 || fd < 0)
	{
		perror((*parse)->str);
		g_sig.return_value = 1;
		while ((*parse) && ft_strcmp((*parse)->str, "|") != 0)
			ft_lstdel_current(&(*parse));
		return ;
	}
	dup2(fd, STDIN_FILENO);
	ft_lstdel_front(&(*parse));
}

void	output_redirection(t_list **parse)
{
	int	fd;

	ft_lstdel_current(&(*parse));
	fd = open((*parse)->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror((*parse)->str);
		g_sig.return_value = 1;
		while ((*parse) && ft_strcmp((*parse)->str, "|") != 0)
			ft_lstdel_current(&(*parse));
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_lstdel_current(&(*parse));
}

void	ft_append(t_list **parse)
{
	int	fd;

	ft_lstdel_current(&(*parse));
	fd = open((*parse)->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror((*parse)->str);
		g_sig.return_value = 1;
		while ((*parse) && ft_strcmp((*parse)->str, "|") != 0)
			ft_lstdel_current(&(*parse));
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_lstdel_current(&(*parse));
}

void	redirection_while(t_parsing *parse)
{
	if (ft_strcmp(parse->lst_cmdline->str, "<") == 0)
	{
		input_redirection(&parse->lst_cmdline);
		if (g_sig.return_value != 1)
			parse->redirection_in = 1;
	}
	else if (ft_strcmp(parse->lst_cmdline->str, ">") == 0)
	{
		parse->redirection_out = 1;
		output_redirection(&parse->lst_cmdline);
	}
	else if (ft_strcmp(parse->lst_cmdline->str, ">>") == 0)
	{
		parse->redirection_out = 1;
		ft_append(&parse->lst_cmdline);
	}
}

void	check_herringbone(t_parsing *parse)
{
	parse->redirection_out = 0;
	while (check_herringbones_input(parse) == 0
		&& parse->lst_cmdline->str[0] != '|' && parse->lst_cmdline != NULL)
	{
		redirection_while(parse);
		if (!parse->lst_cmdline || !parse->lst_cmdline->next
			|| parse->lst_cmdline->str[0] == '|')
			break ;
		if (parse->lst_cmdline->str[0] != '>'
			&& parse->lst_cmdline->str[0] != '<')
			parse->lst_cmdline = parse->lst_cmdline->next;
	}
	if (parse->lst_cmdline)
		while (parse->lst_cmdline->prev != NULL)
			parse->lst_cmdline = parse->lst_cmdline->prev;
}
