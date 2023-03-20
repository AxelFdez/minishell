
#include "../includes/minishell.h"

static int	is_meta_char(int c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

static void	is_quote_string(t_parsing *parse, char c)
{
	parse->i++;
	while (parse->input[parse->i] != c && parse->input[parse->i])
	{
		parse->i++;
		parse->len++;
	}
	ft_fill_lst(&parse->lst_cmdline, parse, parse->i - parse->len);
	parse->len = 0;
	parse->i++;
	return ;
}

static void	is_no_quote_string(t_parsing *parse)
{
	while (parse->input[parse->i] != ' ' && parse->input[parse->i]
		!= '\0' && !is_meta_char(parse->input[parse->i])
		&& parse->input[parse->i] != '\'' && parse->input[parse->i]
		!= '\"')
	{
		parse->len++;
		parse->i++;
	}
	ft_fill_lst(&parse->lst_cmdline, parse, parse->i - parse->len);
	parse->len = 0;
}

// static void	is_continuous_string(t_parsing *parse) // A continuer !!!
// {
// 	while (parse->input[parse->i] != ' ' && parse->input[parse->i]
// 		!= '\0' && !is_meta_char(parse->input[parse->i])
// 		&& parse->input[parse->i] != '\'' && parse->input[parse->i]
// 		!= '\"')
// 	{
// 		parse->len++;
// 		parse->i++;
// 	}
// 	ft_fill_lst(&parse->lst_cmdline, parse, parse->i - parse->len);
// 	parse->len = 0;
// }

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
		// else if (parse->input[parse->i] == '\"' && parse->input[parse->i] != ' ') // A continuer !!!
		// 	is_continuous_string(parse);
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
	int		i;

	ft_initialization(parse);
	ft_quotes(parse);
	i = 0;
	parse->input = ft_strtrim_free_s1(parse->input, " ");
	ft_parseur(parse);
	ft_lstprint_from_head(parse->lst_cmdline);
	printf("input = %s\n", parse->input);
	free(parse->input);
}