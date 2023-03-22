/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind_min.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmassa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:08:33 by chmassa           #+#    #+#             */
/*   Updated: 2023/01/05 16:57:17 by chmassa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstfind_min(t_list **lst)
{
	t_list	*actual;
	int		tmp;
	int		i;
	int		node;

	actual = *lst;
	i = 1;
	node = 1;
	tmp = actual->str;
	while (actual)
	{
		if (actual->next != NULL && actual->next->str < tmp)
		{
			tmp = actual->next->str;
			i++;
			node = i;
		}
		else
			i++;
		actual = actual->next;
	}
	return (node);
}
