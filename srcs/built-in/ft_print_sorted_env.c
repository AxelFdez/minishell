#include "../../includes/minishell.h"

static void	ft_print_env_sorted(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
	{
		ft_putstr("Empty list\n");
		return ;
	}
	tmp = lst;
	while (tmp)
	{
		ft_printf("declare -x %s\n", tmp->str);
		tmp = tmp->next;
	}
}

static void	ft_sortlst_env(t_list **lst)
{
	t_list	*tmp;
	char	*tmp_str;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->next != NULL && ft_strcmp(tmp->str, tmp->next->str) >= 0)
		{
			tmp_str = tmp->str;
			tmp->str = tmp->next->str;
			tmp->next->str = tmp_str;
			tmp = *lst;
		}
		else
			tmp = tmp->next;
	}
}

void	ft_print_sorted_env(t_parsing *parse)
{
	t_list	*envcpy;

	envcpy = ft_lstcpy(&parse->lst_env);
	ft_sortlst_env(&envcpy);
	ft_print_env_sorted(envcpy);
	ft_lstdel_all(&envcpy);
}
