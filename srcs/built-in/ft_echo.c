#include "../../includes/minishell.h"


void	ft_echo(t_list *tmp, t_parsing *parse, int nl)
{
	tmp = tmp->next;
	while (tmp)
	{
		if (ft_strscmp(parse->meta, tmp->str) == 0)
			ft_putstr_fd(tmp->str, 1);
		tmp = tmp->next;
		if (tmp != NULL && ft_strscmp(parse->meta, tmp->str) == 0)
			write(1, " ", 1);
	}
	if (nl == 1)
		write(1, "\n", 1);
}
