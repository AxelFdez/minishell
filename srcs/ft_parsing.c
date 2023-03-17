
#include "../includes/minishell.h"

void	ft_fill_lst(t_list **lst, t_parsing *parse, int len, int start)
{
	t_list	*new;

	new = ft_lstnew(ft_substr(parse->input, parse->i - start, len));
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

static void	ft_parseur(t_parsing *parse)
{
	parse->lst_cmdline = NULL;
	parse->i = 0;
	int	len;

	len = 0;
	while (parse->input[parse->i])
	{
		if (parse->input[parse->i] == '<' && !is_open_herringbone(parse))
				return ;
		if (parse->input[parse->i] == '>' && !is_close_herringbone(parse))
				return ;
		if (parse->input[parse->i] == '|' && !is_pipe(parse))
				return ;
		if (!is_cmd(parse->input[parse->i]))
		{puts("if no | < >");
			while (1)
			{puts("while");
				len++;
				if (!is_cmd(parse->input[parse->i]))
				{puts("IF");

					ft_fill_lst(&parse->lst_cmdline, parse, len,  parse->i);
					printf("len = %d\n", len);
					printf("i = %d\n", parse->i);
					len = 0;
					break ;
				}

				parse->i++;
			}
		}
		parse->i++;

	}
	ft_lstprint_from_head(parse->lst_cmdline);
}

void	*args_list(t_parsing *parse)
{
	int	i;
	int j;
	char temp[256];
	t_list *list_arg = NULL;

	i = 0;
	while (parse->input[i])
	{
		j = 0;
		while (ft_isalnum(parse->input[i]) == 1)
		{
			temp[j] = parse->input[i];
			j++;
			if (ft_isalpha(parse->input[i + 1]) == 0)
			{
				temp[j + 1] = '\0';
				ft_lstadd_back(&parse->lst_cmdline, ft_lstnew(temp));
				break;
			}
			i++;
		}
	// 	j = 0;
	// 	while (input[i] == '<')
	// 	{
	// 		tab[k][j] = input[i];
	// 		j++;
	// 		i++;
	// 		if (input[i] != '<')
	// 		{
	// 			tab[k][j] = '\0';
	// 			k++;
	// 		}
	// 	}
	// 	j = 0;
	// 	while (input[i] == '>')
	// 	{
	// 		tab[k][j] = input[i];
	// 		j++;
	// 		i++;
	// 		if (input[i] != '>')
	// 		{
	// 			tab[k][j] = '\0';
	// 			k++;
	// 		}
	// 	}
	// 	j = 0;
	// 	while (input[i] == '|')
	// 	{
	// 		tab[k][j] = input[i];
	// 		j++;
	// 		i++;
	// 		if (input[i] != '|')
	// 		{
	// 			tab[k][j] = '\0';
	// 			k++;
	// 		}
	// 	}
	// 	i++;
	// }
	// j = 0;
	// tab[k][j] = '\0';
	i++;
	}
	return (list_arg);
}

void	ft_get_cmdline(t_parsing *parse)
{
	int		i;
	parse->lst_cmdline = NULL;

	ft_quotes(parse);
	i = 0;
	parse->input = ft_strtrim_free_s1(parse->input, " ");
	args_list(parse);
	ft_lstprint_from_head(parse->lst_cmdline);
	exit(EXIT_FAILURE);
	ft_parseur(parse);
	printf("input = %s\n", parse->input);
	free(parse->input);
}