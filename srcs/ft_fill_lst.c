#include "../includes/minishell.h"

void	ft_fill_lst(t_list **lst, t_parsing *parse, int start)
{
	t_list	*new;

	new = ft_lstnew(ft_substr(parse->input, start, parse->len));
	ft_lstadd_back(lst, new);
}
