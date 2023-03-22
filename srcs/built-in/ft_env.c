#include "../../includes/minishell.h"

void	ft_env(t_parsing *parse)
{
	t_list	*tmp;

	if (!parse->lst_env)
	{
		ft_putstr_fd("Error print env\n", 2);
		return ;
	}
	tmp = parse->lst_env;
	while (tmp)
	{
		ft_printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
}