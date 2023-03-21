#include "../includes/minishell.h"

void	ft_initialization(t_parsing *parse)
{
	parse->lst_cmdline = NULL;
	parse->i = 0;
	parse->len = 0;
	parse->quote_to_del = 0;
	parse->meta[0] = "<";
	parse->meta[1] = "<<";
	parse->meta[2] = "|";
	parse->meta[3] = ">";
	parse->meta[4] = ">>";
	parse->meta[5] = NULL;
}