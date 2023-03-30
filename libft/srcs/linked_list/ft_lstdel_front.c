/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axfernan <axfernan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:11:01 by chmassa           #+#    #+#             */
/*   Updated: 2023/03/30 23:38:42 by axfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_front(t_list **lst)
{
	t_list *temp;

	if (!(*lst))
		return ;
	if ((*lst)->next)
	{
		temp = (*lst)->next;
		free((*lst)->str);
		free((*lst));
		*lst = temp;
		(*lst)->prev = NULL;
	}
	else
	{
		free((*lst)->str);
		free((*lst));
		*lst = NULL;
	}
}
