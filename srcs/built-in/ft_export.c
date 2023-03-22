#include "../../includes/minishell.h"


//tmp1->next = tmp2->next
//tmp2->prev = tmp1->prev
//tmp1->prev = tmp2
//tmp2->next = tmp1
//start->next = tmp2
//end->prev = tmp1

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

static void	ft_print_sorted_env(t_parsing *parse)
{
	t_list	*envcpy;

	envcpy = ft_lstcpy(&parse->lst_env);
	ft_lstprint_from_head(envcpy);
	ft_sortlst_env(&envcpy);
	ft_print_env_sorted(envcpy);

	exit (0);


	// ft_sortlst_str(&parse->lst_env);
}

void	ft_export(t_parsing *parse)
{
	ft_print_sorted_env(parse);
}
