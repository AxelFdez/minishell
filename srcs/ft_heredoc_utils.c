#include "../includes/minishell.h"

void	check_heredoc(t_parsing *parse)
{
	parse->redirection_in = 0;
	parse->heredoc_pfd = 0;
	while (check_herringbones_input(parse) == 0 && parse->lst_cmdline->str[0] != '|' && parse->lst_cmdline != NULL)
	{
		if (ft_strcmp(parse->lst_cmdline->str, "<<") == 0)
		{
			parse->redirection_in = 1;
			ft_heredoc(parse, &parse->lst_cmdline);
			if (!parse->lst_cmdline)
				return;
		}
		if (!parse->lst_cmdline || !parse->lst_cmdline->next || parse->lst_cmdline->str[0] == '|')
			break;
		if (ft_strcmp(parse->lst_cmdline->str, "<<") != 0)
			parse->lst_cmdline = parse->lst_cmdline->next;
	}
	while (parse->lst_cmdline->prev != NULL)
		parse->lst_cmdline = parse->lst_cmdline->prev;
}