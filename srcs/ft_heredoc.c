/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axfernan <axfernan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 10:49:29 by axfernan          #+#    #+#             */
/*   Updated: 2023/04/20 11:17:55 by axfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_heredocs(t_list **lst)
{
	t_list	*temp_list;
	int		i;

	i = 0;
	temp_list = (*lst);
	while (temp_list && ft_strcmp(temp_list->str, "|") != 0)
	{
		if (ft_strcmp(temp_list->str, "<<") == 0)
			i++;
		temp_list = temp_list->next;
	}
	return (i);
}

static char	**chained_heredoc(t_list **lst, t_parsing *parse)
{
	parse->heredoc_count = count_heredocs(lst);
	parse->heredoc_tab = malloc(sizeof(char *) * (parse->heredoc_count + 1));
	if (!parse->heredoc_tab)
		perror("malloc error");
	parse->heredoc_count = 0;
	while ((*lst) && (*lst)->next && ft_strcmp((*lst)->str, "|") != 0)
	{
		if (ft_strcmp((*lst)->str, "<<") == 0)
		{
			ft_lstdel_current(&(*lst));
			parse->heredoc_tab[parse->heredoc_count] = ft_strdup((*lst)->str);
			parse->heredoc_count++;
			ft_lstdel_current(&(*lst));
		}
		else
			(*lst) = (*lst)->next;
	}
	parse->heredoc_tab[parse->heredoc_count] = 0;
	return (parse->heredoc_tab);
}

static void	heredoc_while(t_parsing *parse, int pfd[2], char *temp)
{
	int	j;

	j = 0;
	while (1)
	{
		temp = readline("> ");
		if (!temp)
			exit(0);
		if (parse->heredoc_count == 1)
		{
			if (ft_strcmp(temp, parse->heredoc_tab[j]) == 0)
				exit(0);
			temp = ft_handle_dollar_in_heredoc(parse, temp);
			ft_putstr_fd(temp, pfd[1]);
			ft_putstr_fd("\n", pfd[1]);
		}
		if (parse->heredoc_count > 1)
		{
			if (ft_strcmp(temp, parse->heredoc_tab[j]) == 0)
			{
				j++;
				parse->heredoc_count--;
			}
		}
	}
}

static void	ft_heredoc_father(t_parsing *parse, int pfd[2])
{
	int	i;

	i = 0;
	waitpid(g_sig.child_heredoc, &parse->heredoc_status, 0);
	if (WIFSIGNALED(parse->heredoc_status))
		ft_lstdel_all(&parse->lst_cmdline);
	g_sig.int_heredoc = 0;
	close(pfd[1]);
	parse->heredoc_pfd = pfd[0];
	while (parse->heredoc_tab[i])
	{
		free(parse->heredoc_tab[i]);
		i++;
	}
	free(parse->heredoc_tab);
}

void	ft_heredoc(t_parsing *parse, t_list **lst)
{
	char	*temp;
	int		pfd[2];

	chained_heredoc(lst, parse);
	temp = "";
	pipe(pfd);
	g_sig.child_heredoc = fork();
	if (g_sig.child_heredoc < 0)
		perror("fork error\n");
	else if (g_sig.child_heredoc == 0)
	{
		g_sig.heredoc = g_sig.child_heredoc;
		close(pfd[0]);
		heredoc_while(parse, pfd, temp);
	}
	ft_heredoc_father(parse, pfd);
	if (!parse->lst_cmdline)
	{
		close(pfd[0]);
		return ;
	}
	else
		while ((*lst)->prev != NULL)
			(*lst) = (*lst)->prev;
}
