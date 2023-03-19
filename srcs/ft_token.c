#include "../includes/minishell.h"

int	is_close_herringbone(t_parsing *parse)
{
	if (parse->input[parse->i] == '>' && parse->input[parse->i +1] == '>')
	{
		parse->len = 2;
		ft_fill_lst(&parse->lst_cmdline, parse, 0, 0);
	}
	if ((parse->input[parse->i] == '>' && parse->input[parse->i +2] == '>')
		|| (parse->input[parse->i] == '>' && parse->input[parse->i -2] == '>'))
	{
		ft_error("syntax error near unexpected token `<'\n");
		return (0);
	}
	else if (parse->input[parse->i] == '>' && parse->input[parse->i +1] != '>'
		&& parse->input[parse->i -1] != '>')
		{
			parse->len = 1;
			ft_fill_lst(&parse->lst_cmdline, parse, 0, 0);
			parse->len = 0;
		}

	return (1);
}

int	is_open_herringbone(t_parsing *parse)
{
	if (parse->input[parse->i] == '<' && parse->input[parse->i +1] == '<')
	{
		parse->len = 2;
		ft_fill_lst(&parse->lst_cmdline, parse, 0, 0);
	}
	if ((parse->input[parse->i] == '<' && parse->input[parse->i +2] == '<')
		|| (parse->input[parse->i] == '<' && parse->input[parse->i -2] == '<'))
	{
		ft_error("syntax error near unexpected token `<'\n");
		return (0);
	}
	else if (parse->input[parse->i] == '<' && parse->input[parse->i +1] != '<'
		&& parse->input[parse->i -1] != '<')
		{
			parse->len = 1;
			ft_fill_lst(&parse->lst_cmdline, parse, 0, 0);
		}
	parse->len = 0;
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
	{
		parse->len = 1;
		ft_fill_lst(&parse->lst_cmdline, parse, 0, 0);
		parse->len = 0;
	}

	return (1);

}