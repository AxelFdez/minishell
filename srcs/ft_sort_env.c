/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axfernan <axfernan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:31:43 by axfernan          #+#    #+#             */
/*   Updated: 2023/04/20 11:31:44 by axfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sort_env(t_list **lst)
{
	t_list	*tmp;
	char	*tmp_str;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->next != NULL && ft_strcmp(tmp->str, tmp->next->str) > 0)
		{
			tmp_str = tmp->str;
			tmp->str = tmp->next->str;
			tmp->next->str = tmp_str;
			tmp = *lst;
		}
		else
			tmp = tmp->next;
	}
}
