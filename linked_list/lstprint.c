/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstprint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmassa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:12:15 by chmassa           #+#    #+#             */
/*   Updated: 2023/01/05 15:20:08 by chmassa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

void	lstprint(t_list *lst)
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
	puts("***********************");
	puts("****** from head ******");
	puts("***********************");
	while(tmp)
	{
		printf("node -> %2d| value = %3s|\n", node, tmp->str);
		tmp = tmp->next;
		node++;
	}
	node = ft_lstsize(lst);
	tmp = ft_lstlast(lst);
	puts("\n***********************");
	puts("****** from tail ******");
	puts("***********************");
	while(tmp)
	{
		printf("node -> %2d| value = %3s|\n", node, tmp->str);
		tmp = tmp->prev;
		node--;
	}
}

