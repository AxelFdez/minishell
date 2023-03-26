/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_actual.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:59:05 by chris             #+#    #+#             */
/*   Updated: 2023/03/26 19:52:08 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_actual(t_list *lst)
{
    // puts("IN FUNC");
    // printf("tmp = %s\n", lst->str);

    t_list  *tmp;

    tmp = lst;
    
    if (tmp->next == NULL)
    {puts("IF");
         tmp->prev->next = NULL;
        free(tmp);
    }
    else if (tmp->prev == NULL)
    {puts("ELSE IF");
        printf("lst = %s\n", lst->str);
        printf("lst next = %s\n", lst->next->str);

        lst = lst->next;
        lst->prev = NULL;
        
        free(tmp);
    }
    else
    {puts("ELSE");
        printf("tmp = %s\n", lst->str);
        tmp = lst;
        lst = lst->prev;
        lst->next = lst->next->next;
        lst->next->prev = lst;
        free(tmp);
        
       
    }
}
