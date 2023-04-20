#include "../includes/minishell.h"

static void	ft_handle_quotes(t_parsing *parse)
{
	parse->is_in_str = 1;
	parse->c = parse->input[parse->i];
	parse->i++;
	parse->len++;
	while (parse->input[parse->i] != parse->c)
	{
		if (parse->c == '\"' && parse->input[parse->i] == '$'
			&& parse->input[parse->i +1] != ' '
			&& parse->input[parse->i +1] != '\0'
			&& parse->input[parse->i +1] != '\"')
			ft_handle_dollar(parse);
		else
		{
			parse->i++;
			parse->len++;
		}
	}
	parse->quote_to_del++;
}

static void	ft_manage_dollar(t_parsing *parse)
{
	while (parse->input[parse->i] == '$' && parse->input[parse->i +1] != ' '
			&& parse->input[parse->i +1] != '\0')
	{
		ft_handle_dollar(parse);
		while (parse->input[parse->i] == '$' && parse->input[parse->i +1] == '$')
		{
			parse->len++;
			parse->i++;
		}
		if (parse->input[parse->i] == ' ')
		{
			parse->i--;
			parse->len--;
			return ;
		}
	}
}

void	is_no_quote_string(t_parsing *parse)
{
	while (parse->input[parse->i] && !is_meta_char(parse->input[parse->i])
		&& parse->input[parse->i] != ' ')
	{
		if (parse->input[parse->i] == '$'
			&& ft_found_char(parse->non_bl_chars, parse->input[parse->i +1]))
            {
			    parse->len += 2;
			    parse->i += 2;
            }
		if (parse->input[parse->i] == '$' && parse->input[parse->i +1] != ' '
			&& parse->input[parse->i +1] != '\0')
			ft_manage_dollar(parse);
		if ((parse->input[parse->i] == '\"' || parse->input[parse->i]
				== '\'') && (parse->input[parse->i +1] != '\0'))
			ft_handle_quotes(parse);
		parse->len++;
		parse->i++;
	}
	ft_fill_lst(&parse->lst_cmdline, parse, parse->i - parse->len);
	parse->len = 0;
}
