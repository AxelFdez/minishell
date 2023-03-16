/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmassa <chrisdev427@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:11:01 by chmassa           #+#    #+#             */
/*   Updated: 2023/03/13 15:16:38 by chmassa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

void	ft_lstdel_front(t_list **lst)
{
	if (!(*lst))
		return ;
	if ((*lst)->next)
	{
		free((*lst));
		*lst = (*lst)->next;
		(*lst)->prev = NULL;
	}
	else
	{
		free((*lst));
		*lst = NULL;
	}
}
