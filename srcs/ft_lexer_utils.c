/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmassa <chmassa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:31:29 by axfernan          #+#    #+#             */
/*   Updated: 2023/04/21 10:13:12 by chmassa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_lexer(t_parsing *parse)
{
	parse->lex[0] = "<<<";
	parse->lex[1] = ">>>";
	parse->lex[2] = "< <";
	parse->lex[3] = "> >";
	parse->lex[4] = "<>";
	parse->lex[5] = "><";
	parse->lex[6] = ">|";
	parse->lex[7] = "<|";
	parse->lex[8] = "|<";
	parse->lex[9] = "|>";
	parse->lex[10] = NULL;
}

void	ft_increment(t_parsing *parse, char c)
{
	parse->i++;
	while (parse->input[parse->i] != c)
		parse->i++;
	parse->i++;
}

int	ft_len_str_to_cmp(t_parsing *parse)
{
	int		j;

	parse->i = 0;
	j = 0;
	while (parse->input[parse->i])
	{
		if (parse->input[parse->i] == '\"')
			ft_increment(parse, '\"');
		else if (parse->input[parse->i] == '\'')
			ft_increment(parse, '\'');
		else
		{
			j++;
			parse->i++;
		}
	}
	return (j);
}

char	*ft_fill_str_to_cmp(t_parsing *parse, char *s)
{
	int	j;

	parse->i = 0;
	j = 0;
	while (parse->input[parse->i])
	{
		if (parse->input[parse->i] == '\"')
			ft_increment(parse, '\"');
		else if (parse->input[parse->i] == '\'')
			ft_increment(parse, '\'');
		else
		{
			s[j] = parse->input[parse->i];
			j++;
			parse->i++;
		}
	}
	s[j] = '\0';
	return (s);
}
