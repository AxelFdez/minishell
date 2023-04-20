/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axfernan <axfernan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:31:35 by axfernan          #+#    #+#             */
/*   Updated: 2023/04/20 21:49:02 by axfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_parseur(t_parsing *parse)
{
	while (parse->input[parse->i])
	{
		if (parse->input[parse->i] == '<' && !is_open_herringbone(parse))
			return ;
		else if (parse->input[parse->i] == '>' && !is_close_herringbone(parse))
			return ;
		else if (parse->input[parse->i] == '|' && !is_pipe(parse))
			return ;
		else if (parse->input[parse->i] == '\"')
			is_quote_string(parse, '\"');
		else if (parse->input[parse->i] == '\'')
			is_quote_string(parse, '\'');
		else if (!is_meta_char(parse->input[parse->i])
			&& parse->input[parse->i] != ' ')
			is_no_quote_string(parse);
		else
			parse->i++;
	}
}

int	ft_get_cmdline(t_parsing *parse)
{
	parse->i = 0;
	parse->is_in_str = 0;
	parse->input = ft_strtrim_free_s1(parse->input, " ");
	if (!ft_str_isspaces(parse->input))
	{
		free(parse->input);
		parse->input = NULL;
		return (0);
	}
	ft_parseur(parse);
	if (ft_check_double_pipes(parse->lst_cmdline))
		return (0);
	//ft_lstprint_from_head(parse->lst_cmdline);
	ft_handle_underscore(parse);
	if (parse->lst_cmdline)
		return (1);
	return (0);
}
