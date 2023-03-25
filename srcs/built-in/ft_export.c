#include "../../includes/minishell.h"


void	ft_export(t_parsing *parse)
{
	printf("exp = %s\n", parse->lst_cmdline->next->str);
}
