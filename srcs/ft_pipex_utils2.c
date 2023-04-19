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

void	delete_cmd(t_list **list_cmd)
{
	while (ft_strcmp((*list_cmd)->str, "|") != 0)
				ft_lstdel_front(&(*list_cmd));
			ft_lstdel_front(&(*list_cmd));
}

int ft_lst_strchr_pipe(t_list *list)
{
	t_list *temp;
	temp = list;

	while (temp)
	{
		if (ft_strcmp(temp->str, "|") == 0)
			return (0);
		temp = temp->next;
	}
	return (1);
}
