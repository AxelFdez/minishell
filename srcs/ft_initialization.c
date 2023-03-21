#include "../includes/minishell.h"

void	ft_initialization(t_parsing *parse)
{
	parse->lst_cmdline = NULL;
	parse->i = 0;
	parse->len = 0;
	parse->quote_to_del = 0;
}