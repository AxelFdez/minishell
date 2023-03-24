/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmassa <chrisdev427@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 14:08:25 by chmassa           #+#    #+#             */
/*   Updated: 2023/03/22 15:05:14 by chmassa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcpy(t_list **lst)
{
	t_list	*lstcpy;
	t_list	*tmp;
	t_list	*new;

	tmp = *lst;
	lstcpy = NULL;
	while (tmp)
	{
		new = ft_lstnew(tmp->str);
		ft_lstadd_back(&lstcpy, new);
		tmp = tmp->next;
	}
	return (lstcpy);
}
