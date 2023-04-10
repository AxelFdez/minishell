/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:11:54 by chmassa           #+#    #+#             */
/*   Updated: 2023/04/08 08:59:09 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lst_to_str(t_list *lst)
{
	char	*str;
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	str = ft_calloc(1, sizeof(char));
	while (tmp)
	{
		str = ft_strjoin_free_s1(str, tmp->str);
		tmp = tmp->next;
	}
	return (str);
}
