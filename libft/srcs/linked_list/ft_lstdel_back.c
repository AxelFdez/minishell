/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmassa <chrisdev427@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:08:22 by chmassa           #+#    #+#             */
/*   Updated: 2023/03/22 11:06:51 by chmassa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_back(t_list **lst)
{
	t_list	*tmp;

	if (!(*lst))
		return ;
	tmp = *lst;
	if (tmp->next == NULL)
	{
		free(tmp);
		*lst = NULL;
	}
	else
	{
		while (tmp)
		{
			if (tmp->next->next == NULL)
			{
				tmp->next->prev = NULL;
				tmp->next = NULL;
				free(tmp->next);
			}
			tmp = tmp->next;
		}
	}
}