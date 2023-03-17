#include "../includes/minishell.h"

int	is_close_herringbone(t_parsing *parse)
{
	if (parse->input[parse->i] == '>' && parse->input[parse->i +1] == '>')
			ft_fill_lst(&parse->lst_cmdline, parse, 2, 0);
	if ((parse->input[parse->i] == '>' && parse->input[parse->i +2] == '>')
		|| (parse->input[parse->i] == '>' && parse->input[parse->i -2] == '>'))
	{
		ft_error("syntax error near unexpected token `<'\n");
		return (0);
	}
	else if (parse->input[parse->i] == '>' && parse->input[parse->i +1] != '>'
		&& parse->input[parse->i -1] != '>')
			ft_fill_lst(&parse->lst_cmdline, parse, 1, 0);
	// parse->i++;
	
	return (1);
}

int	is_open_herringbone(t_parsing *parse)
{
	if (parse->input[parse->i] == '<' && parse->input[parse->i +1] == '<')
			ft_fill_lst(&parse->lst_cmdline, parse, 2, 0);
	if ((parse->input[parse->i] == '<' && parse->input[parse->i +2] == '<')
		|| (parse->input[parse->i] == '<' && parse->input[parse->i -2] == '<'))
	{
		ft_error("syntax error near unexpected token `<'\n");
		return (0);
	}
	else if (parse->input[parse->i] == '<' && parse->input[parse->i +1] != '<'
		&& parse->input[parse->i -1] != '<')
			ft_fill_lst(&parse->lst_cmdline, parse, 1, 0);
	// parse->i++;
	return (1);
}

int is_pipe(t_parsing *parse)
{
	if (parse->input[parse->i] == '|' && parse->input[parse->i +1] == '|')
	{
		ft_error("syntax error near unexpected token `<'\n");
		return (0);
	}
	if (parse->input[parse->i] == '|')
			ft_fill_lst(&parse->lst_cmdline, parse, 1, 0);
	// parse->i++;
	
	return (1);

}