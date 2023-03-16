
#include "../includes/minishell.h"

void	ft_fill_lst(t_list **lst, t_parsing *parse, int start, int len)
{
	t_list	*new;

	new = ft_lstnew(ft_substr(parse->input, start, len));				
	ft_lstadd_back(lst, new);
	free(parse->tmp);
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

void	ft_get_cmdline(t_parsing *parse)
{
	int		i;

	ft_quotes(parse);
	i = 0;
	parse->input = ft_strtrim_free_s1(parse->input, " ");
	ft_parseur(parse);
	// printf("input = %s\n", parse->input);
	free(parse->input);
}