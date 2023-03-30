/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axfernan <axfernan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:11:01 by chmassa           #+#    #+#             */
/*   Updated: 2023/03/30 10:15:53 by axfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_front(t_list **lst)
{
	if (!(*lst))
		return ;
	if ((*lst)->next)
	{
		free((*lst)->str);
		free((*lst));
		*lst = (*lst)->next;
		(*lst)->prev = NULL;
	}
	else
	{
		free((*lst)->str);
		free((*lst));
		*lst = NULL;
	}
}
