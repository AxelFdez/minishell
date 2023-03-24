/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_position.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmassa <chrisdev427@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:14:49 by chmassa           #+#    #+#             */
/*   Updated: 2023/03/22 11:06:59 by chmassa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_position(t_list **lst, int position)
{
	int		i;
	t_list	*tmp;

	if (!(*lst))
		return ;
	if (position < 2 || position >= ft_lstsize(*lst))
		return ;
	i = 2;
	tmp = *lst;
	while (tmp)
	{
		if (i == position)
		{
			free(tmp->next);
			tmp->next = tmp->next->next;
			tmp->next->prev = tmp;
		}
		tmp = tmp->next;
		i++;
	}
}
