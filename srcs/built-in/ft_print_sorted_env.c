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
static char	*ft_add_quotes(char *s)
{
	char	*str;
	int		i;
	int		j;
	int		check_equal;
	
	i = 0;
	j = 0;
	check_equal = 0;
	str = malloc(sizeof(char) * (ft_strlen(s) + 3));
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '=' && check_equal == 0)
		{
			str[j++] = s[i++];
			str[j++] = '\"';
			check_equal++;
		}
		else
			str[j++] = s[i++];
	}
	str[j] = '\"';
	str[j +1] = '\0';
	return (str);
}

static t_list	*ft_env_cpy(t_list **lst)
{
	t_list	*lstcpy;
	t_list	*tmp;
	t_list	*new;
	

	tmp = *lst;
	lstcpy = NULL;
	while (tmp)
	{
		new = ft_lstnew(ft_add_quotes(tmp->str));
		ft_lstadd_back(&lstcpy, new);
		tmp = tmp->next;
	}
	return (lstcpy);
}


void	ft_print_sorted_env(t_parsing *parse)
{
	t_list	*envcpy;

	envcpy = ft_env_cpy(&parse->lst_env);
	ft_sortlst_env(&envcpy);
	ft_print_env_sorted(envcpy);
	ft_lstdel_all(&envcpy);
}
