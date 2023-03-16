/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmassa <chrisdev427@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 14:08:25 by chmassa           #+#    #+#             */
/*   Updated: 2023/03/13 14:49:04 by chmassa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst.h"

t_list	*ft_lstcpy(t_list **lst)
{
	t_list	*lstcpy;
	t_list	*tmp;
	t_list	*new;

	tmp = *lst;
	while (tmp)
	{
		new = ft_lstnew(tmp->str);
		ft_lstadd_back(&lstcpy, new);
		tmp = tmp->next;
	}


	return (lstcpy);
}
