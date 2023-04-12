/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_char_tab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmassa <chmassa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:14:32 by chmassa           #+#    #+#             */
/*   Updated: 2023/04/12 18:18:39 by chmassa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lst_to_char_tab(t_list *lst)
{
	t_list	*tmp;
	char	**array;
	int		i;

	if (!lst)
		return (NULL);
	i = 0;
	tmp = lst;
	array = malloc(sizeof (char *) * (ft_lstsize(lst) + 1));
	while (tmp)
	{
		array[i] = ft_strdup(tmp->str);
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}
