/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axfernan <axfernan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:08:09 by axfernan          #+#    #+#             */
/*   Updated: 2023/04/21 12:16:45 by axfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	del_parsed_cmd(t_parsing *parse)
{
	int	i;

	i = 0;
	if (parse->built_in_cmd > 0)
	{
		while (i < parse->lst_target + 1)
		{
			parse->built_in_cmd = 0;
			ft_lstdel_front(&parse->lst_cmdline);
			i++;
		}
	}
}

void	print_list(t_list *lst)
{
	if (!lst)
	{
		ft_printf("la liste est vide\n");
		return ;
	}
	while (lst != NULL)
	{
		ft_putstr_fd(lst->str, 2);
		lst = lst->next;
	}
	ft_printf("\n");
}

void	delete_cmd(t_list **list_cmd)
{
	if (!(*list_cmd))
		return ;
	while (ft_strcmp((*list_cmd)->str, "|") != 0)
		ft_lstdel_front(&(*list_cmd));
	ft_lstdel_front(&(*list_cmd));
}

int	ft_lst_strchr_pipe(t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp)
	{
		if (ft_strcmp(temp->str, "|") == 0)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int	check_builtin_input(t_parsing *parse)
{
	char	*tmp;

	tmp = parse->lst_cmdline->str;
	if (ft_strcmp(tmp, "env") == 0 || ft_strcmp(tmp, "ENV") == 0
		|| ft_strcmp(tmp, "export") == 0 || ft_strcmp(tmp, "pwd") == 0
		|| ft_strcmp(tmp, "PWD") == 0 || ft_strcmp(tmp, "echo") == 0
		|| ft_strcmp(tmp, "unset") == 0 || ft_strcmp(tmp, "cd") == 0
		|| ((ft_strcmp(tmp, "cd") == 0 && (ft_strcmp(tmp, "~"))))
		|| ft_strcmp(tmp, "exit") == 0 || ft_strcmp(tmp, "history") == 0)
	{
		return (0);
	}
	return (1);
}
