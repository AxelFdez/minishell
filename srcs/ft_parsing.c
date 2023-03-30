#include "../includes/minishell.h"

int	is_meta_char(int c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

static void	is_quote_string(t_parsing *parse, char c)
{
	while (parse->input[parse->i])
	{
		if (parse->input[parse->i] == c && parse->input[parse->i +1] != ' ')
		{
			parse->len++;
			parse->i++;
			parse->quote_to_del++;
		}
		if (parse->input[parse->i] == '$' && parse->input[parse->i +1] != ' ' && c == '\"')
		{
			ft_handle_dollar(parse);
			parse->len = 0;
		}
		if (parse->input[parse->i] == c && parse->input[parse->i +1] == ' ')
		{
			parse->i++;
			parse->len++;
			break ;
		}
		parse->i++;
		parse->len++;
	}
	ft_fill_lst(&parse->lst_cmdline, parse, parse->i - parse->len);
	parse->len = 0;
	parse->quote_to_del = 0;
}

static void	is_no_quote_string(t_parsing *parse)
{
	while (parse->input[parse->i] && !is_meta_char(parse->input[parse->i])
		&& parse->input[parse->i] != ' ')
	{
		if (parse->input[parse->i] == '$' && parse->input[parse->i +1] != ' ' && parse->input[parse->i +1] != '\0')
		{
			ft_handle_dollar(parse);
			parse->len = 0;
			if (parse->input[parse->i] == ' ')
				break ;
		}
		if (parse->input[parse->i] == '\"' || parse->input[parse->i] == '\'')
		{
			parse->c = parse->input[parse->i];
			parse->i++;
			parse->len++;
			while (parse->input[parse->i] != parse->c)
			{
				parse->len++;
				parse->i++;
			}
			parse->quote_to_del++;
		}
		parse->len++;
		parse->i++;
	}
	ft_fill_lst(&parse->lst_cmdline, parse, parse->i - parse->len);
	parse->len = 0;
	parse->quote_to_del = 0;
}

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

void	ft_get_cmdline(t_parsing *parse)
{
	parse->input = ft_strtrim_free_s1(parse->input, " ");
	parse->ret_value = ft_check_syntax(parse);
	ft_parseur(parse);
	//ft_lstprint_from_head(parse->lst_cmdline);
	//ft_lstdel_all(&parse->lst_cmdline);
	// ft_lstprint_from_head(parse->lst_cmdline);
	//ft_lstdel_all(&parse->lst_cmdline);
	free(parse->input);
}
// 	ft_check_built_in(parse);
// 	ft_lstprint_from_head(parse->lst_cmdline);
// 	ft_lstdel_all(&parse->lst_cmdline);
// 	free(parse->input);

// }
