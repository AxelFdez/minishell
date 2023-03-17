
#include "../includes/minishell.h"

void	ft_fill_lst(t_list **lst, t_parsing *parse, int start)
{
	t_list	*new;
	
	new = ft_lstnew(ft_substr(parse->input, start, parse->len));				
	ft_lstadd_back(lst, new);
	
}

int	is_cmd(int c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	// if (c >= 32 && c <= 126)
	// 	return (1);
	return (0);
}

static void	is_string(t_parsing *parse, char c)
{
	while (parse->input[parse->i])
	{
		// parse->i++;

		if (parse->input[parse->i] == c)
		{
			ft_fill_lst(&parse->lst_cmdline, parse, parse->i - parse->len);
			parse->len = 0;
			// parse->i++;
			return ;
		}
		parse->i++;
		parse->len++;
	}
}


static void	ft_parseur(t_parsing *parse)
{
	parse->lst_cmdline = NULL;
	parse->i = 0;
	
	
	parse->len = 0;
	while (parse->input[parse->i])
	{
		if (parse->input[parse->i] == '<' && !is_open_herringbone(parse))
				return ;
	 	else if (parse->input[parse->i] == '>' && !is_close_herringbone(parse))
				return ;
	 	else if (parse->input[parse->i] == '|' && !is_pipe(parse))
				return ;
	 	else if (parse->input[parse->i] == '\"')
		{
			parse->i++;
			is_string(parse, '\"');
		}
	 	else if (parse->input[parse->i] == '\'')
		{
			parse->i++;
			is_string(parse, '\'');
		}
		
	 	else if (!is_cmd(parse->input[parse->i]) && parse->input[parse->i] != ' ')
		{puts("AAA");
			printf("i = %d\n", parse->i);

			while (parse->input[parse->i])
			{
				parse->len++;
				parse->i++;
				if (parse->input[parse->i] == ' ' || parse->input[parse->i] == '\0' || is_cmd(parse->input[parse->i] || parse->input[parse->i] == '\"'))
				{puts("BBB");
					ft_fill_lst(&parse->lst_cmdline, parse, parse->i - parse->len);
					parse->len = 0;
			printf("i = %d\n", parse->i);

					break ;
				}
			}

			printf("len = %d\n", parse->len);
		}
		else
				parse->i++;
	}
	ft_lstprint_from_head(parse->lst_cmdline);
}

void	ft_get_cmdline(t_parsing *parse)
{
	int		i;

	ft_quotes(parse);
	i = 0;
	parse->input = ft_strtrim_free_s1(parse->input, " ");
	ft_parseur(parse);
	printf("input = %s\n", parse->input);
	free(parse->input);
}