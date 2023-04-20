/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axfernan <axfernan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:30:56 by axfernan          #+#    #+#             */
/*   Updated: 2023/04/20 21:56:02 by axfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_found_var_in_env(t_parsing *parse)
{
	t_list	*tmp;

	tmp = parse->lst_env;
	parse->s1 = ft_strdup(parse->var_name);
	while (tmp)
	{
		parse->s2 = ft_set_str_to_comp(tmp->str);
		if (ft_strcmp(parse->s1, parse->s2) == 0)
		{
			if (!parse->str_tmp)
				parse->str_tmp = ft_calloc(1, sizeof(char));
			parse->str_tmp = ft_strjoin_free_s1(parse->str_tmp,
					tmp->str + (ft_strlen(parse->var_name) + 1));
			free(parse->s1);
			free(parse->s2);
			return (0);
		}
		tmp = tmp->next;
		free(parse->s2);
	}
	free(parse->s1);
	return (1);
}

static void	ft_retrieve_var_name(t_parsing *parse)
{
	int	i;

	i = 0;
	parse->i++;
	while (parse->input[parse->i] && parse->input[parse->i] != '\"'
		&& parse->input[parse->i] != '\'' && parse->input[parse->i] != ' '
		&& parse->input[parse->i] != '$'
		&& !ft_found_char(parse->non_bl_chars, parse->input[parse->i]))
	{
		parse->var_name[i] = parse->input[parse->i];
		i++;
		parse->i++;

	}
	parse->var_name[i] = '\0';
	ft_found_var_in_env(parse);
	ft_bzero(parse->var_name, 1024);
}

void	ft_handle_dollar(t_parsing *parse)
{
	char	*ret_itoa;

	if (parse->len > 0 && !parse->str_tmp)
		parse->str_tmp = ft_substr(parse->input,
				parse->i - parse->len, parse->len);
	else if (parse->str_tmp)
		parse->str_tmp = ft_strjoin_free_s1_s2(parse->str_tmp,
				ft_substr(parse->input, parse->i - parse->len, parse->len));
	if (parse->input[parse->i +1] == '?')
	{
		if (parse->str_tmp == NULL)
			parse->str_tmp = ft_calloc(1, sizeof(char));
		ret_itoa = ft_itoa(g_sig.return_value);
		parse->str_tmp = ft_strjoin_free_s1_s2(parse->str_tmp, ret_itoa);
		parse->i += 2;
	}
	else
		ft_retrieve_var_name(parse);
	parse->len = 0;
}
