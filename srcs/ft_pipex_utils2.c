#include "../includes/minishell.h"

void	del_parsed_cmd(t_parsing *parse)
{
	int	i;

	i = 0;
	if (parse->built_in_cmd > 0)
	{
		while (i < parse->lst_target + 1)
		{
			parse->built_in_cmd = 0;
			ft_lstdel_front(&parse->lst_cmdline);
			i++;
		}
	}
}

void	print_list(t_list *lst)
{
	if (!lst)
	{
		ft_printf("la liste est vide\n");
		return ;
	}
	while (lst != NULL)
	{
		dprintf(2, "[%s] ", lst->str);
		lst = lst->next;
	}
	ft_printf("\n");
}