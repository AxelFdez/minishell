/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint_from_head.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmassa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:12:15 by chmassa           #+#    #+#             */
/*   Updated: 2023/01/05 11:45:29 by chmassa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

void	ft_lstprint_from_head(t_list *lst)
{
	t_list	*tmp;
	int		node;

	if (!lst)
	{
		puts("Empty list");
		return ;
	}
	node = 1;
	tmp = lst;
	while(tmp)
	{
		printf("node[%d] value|%s|\n", node, tmp->str);
		tmp = tmp->next;
		node++;
	}
}
