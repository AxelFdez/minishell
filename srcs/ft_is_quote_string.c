#include "../includes/minishell.h"

void	is_quote_string(t_parsing *parse, char c)
{
	parse->i++;
	parse->len++;
	parse->quote_to_del++;
	parse->is_in_str = 1;
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
