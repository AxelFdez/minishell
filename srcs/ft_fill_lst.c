/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmassa <chmassa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:31:08 by axfernan          #+#    #+#             */
/*   Updated: 2023/04/21 11:36:33 by chmassa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_set_str_to_add(t_parsing *parse, t_list **lst, int start)
{
	char	*str;
	char	**tab;
	t_list	*tmp;
	int		i;

	str = NULL;
	i = 0;
	if (parse->str_tmp)
	{
		tab = ft_split(parse->str_tmp, ' ');
		free(parse->str_tmp);
		parse->str_tmp = NULL;
		while (tab[i])
		{
			tmp = ft_lstnew(ft_strdup(tab[i]));
			ft_lstadd_back(lst, tmp);
			free(tab[i]);
			i++;
		}
		free(tab);
		return (NULL);
	}
	else
		str = ft_substr(parse->input, start, parse->len);
	return (str);
}

void	ft_fill_lst(t_list **lst, t_parsing *parse, int start)
{
	t_list	*new;
	char	*str;

	str = ft_set_str_to_add(parse, lst, start);
	if (!str)
		return ;
	if (parse->quote_to_del > 0)
	{
		ft_strdel_quotes(parse, str);
		parse->quote_to_del = 0;
	}
	if (str)
	{
		new = ft_lstnew(ft_strdup(str));
		ft_lstadd_back(lst, new);
		free(str);
	}
}
