/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_dollar_utils_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axfernan <axfernan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:30:52 by axfernan          #+#    #+#             */
/*   Updated: 2023/04/20 11:30:53 by axfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_found_var(t_parsing *parse, char *s)
{
	t_list	*tmp;
	char	*ret;

	if (s[0] == '$' && s[1] == '?')
	{
		ret = ft_strdup_free(ft_itoa(g_sig.return_value));
		return (ret);
	}
	tmp = parse->lst_env;
	parse->s1 = ft_strdup(s +1);
	while (tmp)
	{
		parse->s2 = ft_set_str_to_comp(tmp->str);
		if (ft_strcmp(parse->s1, parse->s2) == 0)
		{
			ret = ft_strdup(tmp->str + ft_strlen(s));
			free(parse->s1);
			free(parse->s2);
			return (ret);
		}
		tmp = tmp->next;
		free(parse->s2);
	}
	free(parse->s1);
	return (NULL);
}

void	ft_replace_value(t_parsing *parse, t_list **lst)
{
	t_list	*tmp;
	char	*ret_var_name;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->str[0] == '$')
		{
			ret_var_name = ft_found_var(parse, tmp->str);
			if (ret_var_name)
			{
				free(tmp->str);
				tmp->str = ft_strdup(ret_var_name);
				free(ret_var_name);
			}
			else if (ft_strlen(tmp->str) > 1)
				ft_lstdel_actual(lst, tmp);
		}
		tmp = tmp->next;
	}
}
