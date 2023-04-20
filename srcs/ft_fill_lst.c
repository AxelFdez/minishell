/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axfernan <axfernan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:31:08 by axfernan          #+#    #+#             */
/*   Updated: 2023/04/20 11:31:09 by axfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_set_str_to_add(t_parsing *parse, int start)
{
	char	*str;

	str = NULL;
	if (parse->str_tmp)
	{
		str = ft_strdup(parse->str_tmp);
		free(parse->str_tmp);
		parse->str_tmp = NULL;
		str = ft_strjoin_free_s1_s2(str,
				ft_substr(parse->input, start, parse->len));
	}
	else
		str = ft_substr(parse->input, start, parse->len);
	return (str);
}

void	ft_fill_lst(t_list **lst, t_parsing *parse, int start)
{
	t_list	*new;
	char	*str;

	str = ft_set_str_to_add(parse, start);
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
