/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmassa <chrisdev427@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:21:49 by chmassa           #+#    #+#             */
/*   Updated: 2023/03/22 11:06:28 by chmassa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!(*lst))
	{
		new->next = *lst;
		*lst = new;
	}
	else
	{
		new->next = *lst;
		*lst = new;
		new->next->prev = new;
	}
}
