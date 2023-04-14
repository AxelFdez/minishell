/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_strcmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmassa <chmassa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:20:03 by chmassa           #+#    #+#             */
/*   Updated: 2023/04/14 10:21:06 by chmassa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int    ft_lst_strcmp(t_list *lst, char *s)
{
    t_list  *tmp;

    if (!lst || !s)
        return (0);
    tmp = lst;
    while (tmp)
    {
        if (ft_strcmp(tmp->str, s) == 0)
            return (1);
        tmp = tmp->next;
    }
    return (0);
}
