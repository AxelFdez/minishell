
#include "../includes/minishell.h"

void	ft_fill_lst(t_list **lst, t_parsing *parse, int start, int len)
{
	t_list	*new;

	new = ft_lstnew(ft_substr(parse->input, start, len));
	ft_lstadd_back(lst, new);

 }

// int	is_cmd(int c)
// {
// 	if (c == '|' || c == '<' || c == '>')
// 		return (1);
// 	// if (c >= 32 && c <= 126)
// 	// 	return (1);
// 	return (0);
// }

// static void	is_string(t_parsing *parse, char c)
// {
// 	while (parse->input[parse->i] != c)
// 	{
// 		parse->i++;
// 		parse->len++;
// 		ft_fill_lst(&parse->lst_cmdline, parse, parse->i - parse->len);
// 		parse->len = 0;
// 	}
// }


// static void	ft_parseur(t_parsing *parse)
// {
// 	parse->lst_cmdline = NULL;
// 	parse->i = 0;


// 	parse->len = 0;
// 	while (parse->input[parse->i])
// 	{
// 		if (parse->input[parse->i] == '<' && !is_open_herringbone(parse))
// 				return ;
// 		else if (parse->input[parse->i] == '>' && !is_close_herringbone(parse))
// 				return ;
// 		else if (parse->input[parse->i] == '|' && !is_pipe(parse))
// 				return ;
// 		else if (parse->input[parse->i] == '\"')
// 			is_string(parse, '\"');
// 		else if (!is_cmd(parse->input[parse->i]))
// 		{
// 			printf("i = %d\n", parse->i);
// 			while (parse->input[parse->i] && !is_cmd(parse->input[parse->i]) && parse->input[parse->i] != ' ')
// 			{
// 				parse->len++;
// 				parse->i++;
// 			}
// 			printf("len = %d\n", parse->len);
// 			ft_fill_lst(&parse->lst_cmdline, parse, parse->i - parse->len);
// 			parse->len = 0;
// 		}
// 			parse->i++;
// 	}
// 	ft_lstprint_from_head(parse->lst_cmdline);
// }

void	*args_list(t_parsing *parse)
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
	return (list_arg);
}

// char **quotes_args(char *input)
// {
// 	int i;
// 	int j;
// 	int k;
// 	char **tab;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	tab = malloc(sizeof(tab));
// 	while (input[i])
// 	{
// 		while (input[i] == '"')
// 		{
// 			i++;
// 			j = 0;
// 			while (input[i] != '"')
// 			{
// 				tab[k][j] = input[i];
// 				j++;
// 				i++;
// 			}
// 			k++;
// 		}
// 		i++;
// 	}
// 	tab[k + 1][0] = '\0';
// 	return (tab);
// }

// char **isolate_dquotes(char *input)
// {
// 	char **tab;
// 	int i;
// 	int j;
// 	int quotes;
// 	int start;

// 	quotes = 0;
// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '"')
// 			quotes++;
// 		i++;
// 	}
// 	printf("quotes = %d\n", quotes);
// 	if (quotes == 0)
// 		quotes = 2;
// 	tab = malloc(sizeof(char *) * ((quotes / 2) + 1));
// 	if (!tab)
// 		perror("malloc error");
// 	i = 0;
// 	j = 0;
// 	start = 0;
// 	while (input[i])
// 	{
// 		if (input[i] != '"')
// 		{
// 			start = i;
// 			while (input[i] != '"')
// 			{
// 				if (input[i + 1] == '"'|| input[i + 1] == '\0' )
// 					break;
// 				i++;
// 			}
// 			tab[j] = ft_substr(input, start, i - start + 1);
// 			j++;
// 		}
// 		if (input[i] == '"')
// 		{
// 			start = i;
// 			i++;
// 			while (input[i] != '"')
// 				i++;
// 			tab[j] = ft_substr(input, start, i - start + 1);
// 			j++;
// 		}
// 		i++;
// 	}
// 	tab[j] = 0;
// 	return (tab);
// }

void isolate_dquotes(t_parsing *parse)
{
	int i;
	int start;

	i = 0;
	start = 0;
	while (parse->input[i])
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
}

// void isolate_squote(t_parsing *parse)
// {
// 	int i;
// 	t_list *temp;

// 	i = 0;
// 	temp = parse->lst_cmdline;
// 	while (temp)
// 	{
// 		if (ft_strchr(temp->str, '"') == NULL)
// 		{
// 			if (ft_strchr(temp->str, '\'') != NULL)
// 			{

// 			}
// 		}
// 		temp = temp->next;
// 	}
// }

int is_dquote_inside_squote(char *input, int quote_pos)
{
	int i;
	int squote;

	i = 0;
	squote = 0;
	while (i < quote_pos)
	{
		if (input[i] == 39)
			squote++;
	}
	squote = squote % 2;
	return (squote);
}

int is_squote_inside_dquote(char *input, int quote_pos)
{
	int i;
	int dquote;

	i = 0;
	dquote = 0;
	while (i < quote_pos)
	{
		if (input[i] == '"')
			dquote++;
	}
	dquote = dquote % 2;
	return (dquote);
}


void	parsing_quotes(t_parsing *parse)
{
	int i;
	int start;
	//int end;

	i = 0;
	start = 0;

	while (1)
	{
		if (parse->input[i + 1] == '\0')
			break;
		if (parse->input[i] != '"' && parse->input[i] != 39 && parse->input[i])
		{
			start = i;
			while (parse->input[i] != '"' && parse->input[i] != 39 && parse->input[i])
				i++;
			ft_fill_lst(&parse->lst_cmdline, parse, start, i - start);
		}
		if (parse->input[i] == '"')
		{
			start = i;
			i++;
			while (parse->input[i] != '"')
				i++;
			ft_fill_lst(&parse->lst_cmdline, parse, start, i - start + 1);
		}
		if (parse->input[i] == 39)
		{
			start = i;
			i++;
			while (parse->input[i] != 39)
				i++;
			ft_fill_lst(&parse->lst_cmdline, parse, start, i - start + 1);
		}
		//ft_fill_lst(&parse->lst_cmdline, parse, start, i - start + 1);
		// if (parse->input[i] == '"' && is_dquote_inside_squote(parse->input, i) == 0)
		// {
		// 	start = i;
		// 	i++;
		// 	while (parse->input[i] != '"')
		// 	{
		// 		// if (parse->input[i + 1] == '"')
		// 		// 	break ;
		// 		i++;
		// 	}
		// 	ft_fill_lst(&parse->lst_cmdline, parse, start, i - start + 1);
		// }
		// else if (parse->input[i] == 39 && is_squote_inside_dquote(parse->input, i) == 0)
		// {
		// 	start = i;
		// 	i++;
		// 	while (parse->input[i] != 39)
		// 		i++;
		// 	ft_fill_lst(&parse->lst_cmdline, parse, start, i - start + 1);
		// }
		}
}

void	ft_get_cmdline(t_parsing *parse)
{
	//int		i = 0;
	//char **split_input = NULL;
	parse->lst_cmdline = NULL;

	ft_quotes(parse);
	//i = 0;
	parse->input = ft_strtrim_free_s1(parse->input, " ");
	//split_input = quotes_args(parse->input);
	// decouper args entre quotes et doubles quotes,
	//if (ft_strchr(parse->input, '"') != NULL || ft_strchr(parse->input, 39) != NULL)
	parsing_quotes(parse);
	//isolate_dquotes(parse);
	//ft_lstprint_from_head(parse->lst_cmdline);
	//split_input = isolate_squote(split_input);
	// decouper selon les espaces (seulement args sans quotes),
	// split_input = ft_split(parse->input, ' ');
	// split_input = ft_split(parse->input, '|');
	// interpreter ou non les quotes
	// decouper selon les chevrons ou pipes
	//ft_parseur(parse);
	//printf("input = %s\n", parse->input);
	free(parse->input);
}