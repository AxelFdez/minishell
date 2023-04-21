/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_quote_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmassa <chmassa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:31:27 by axfernan          #+#    #+#             */
/*   Updated: 2023/04/21 10:17:19 by chmassa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_vars_init(t_parsing *parse)
{
	parse->i++;
	parse->len++;
	parse->quote_to_del++;
	parse->is_in_str = 1;
}

void	is_quote_string(t_parsing *parse, char c)
{
	ft_vars_init(parse);
	while (parse->input[parse->i])
	{
		if (parse->input[parse->i] == '$'
			&& ft_found_char(parse->non_bl_chars, parse->input[parse->i +1]))
			parse->i += 1;
		if (parse->input[parse->i] == '$' && parse->input[parse->i +1] != ' '
			&& parse->input[parse->i +1] != '\"' && c == '\"')
				parse->is_dollar++;
		if (parse->input[parse->i] == c && parse->input[parse->i +1] == ' ')
		{
			parse->i++;
			parse->len++;
			break ;
		}
		parse->i++;
		parse->len++;
	}
	if (parse->is_dollar > 0)
		ft_handle_dollar_in_str(parse);
	else
		ft_fill_lst(&parse->lst_cmdline, parse, parse->i - parse->len);
	parse->len = 0;
}
