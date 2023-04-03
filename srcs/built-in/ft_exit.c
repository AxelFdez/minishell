#include "../../includes/minishell.h"


void	ft_exit(t_parsing *parse)
{
	if (parse->lst_cmdline->next == NULL)
		exit (0);
	else
		ft_lstdel_front(&parse->lst_cmdline);
		ft_lstdel_front(&parse->lst_cmdline);
		// print_list(parse->lst_cmdline);
		// ft_putstr_fd("exit: no argument required\n", 2);
}
