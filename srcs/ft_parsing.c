
#include "../includes/minishell.h"

void	ft_fill_lst(t_list **lst, t_parsing *parse, int start, int len)
{
	t_list	*new;

	new = ft_lstnew(ft_substr(parse->input, start, len));
	ft_lstadd_back(lst, new);
}

static void	ft_herringbone(t_parsing *parse, int i)
{
	if (parse->input[i] == '<' && parse->input[i +1] == '<')
			ft_fill_lst(&parse->lst_cmdline, parse, i, 2);
	else if (parse->input[i] == '<' && parse->input[i +1] == ' ' && parse->input[i +2] == '<')
	{

		ft_error("syntax error near unexpected token `<'");
		return ;
	}
	else if (parse->input[i] == '<' && parse->input[i +1] != '<' && parse->input[i -1] != '<')
			ft_fill_lst(&parse->lst_cmdline, parse, i, 1);
}

static void	ft_parseur(t_parsing *parse)
{
	parse->lst_cmdline = NULL;
	int	i;

	i = 0;
	while (parse->input[i])
	{
		if (parse->input[i] == '<')
			ft_herringbone(parse, i);


		// if (parse->input[i] == '<' && parse->input[i +1] == '<')
		// {
		// 	ft_fill_lst(&parse->lst_cmdline, parse, i, 2);
		// 	i++;
		// }
		// else if (parse->input[i] == '<' && parse->input[i +1] == ' ' && parse->input[i +2] == '<')
		// {
		// 	ft_error(parse, "syntax error near unexpected token `<'");
		// 	return ;
		// }
		// else if (parse->input[i] == '<' && parse->input[i +1] != '<' && parse->input[i -1] != '<')
		// {

		// 	ft_fill_lst(&parse->lst_cmdline, parse, i, 1);
		// }
		i++;
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