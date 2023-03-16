

#include "../includes/minishell.h"

void	ft_error(char *err_mess)
{
	write (2, "Error\n", 6);
	ft_putstr_fd(err_mess, 2);
	// return ;
	// if (parse->lst_cmdline)
	// 	ft_lstdel_all(&parse->lst_cmdline);
	// exit (EXIT_FAILURE);
}