/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnode_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axfernan <axfernan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 13:01:48 by chmassa           #+#    #+#             */
/*   Updated: 2023/04/20 11:37:35 by axfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstnode_value(t_list **lst, int node)
{
	int	value;
	int	position;

	position = 1;
	while (*lst)
	{
		if (position == node)
		{
			value = (*lst)->str;
		}
		*lst = (*lst)->next;
		position ++;
	}
	return (value);
}
