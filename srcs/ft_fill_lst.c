#include "../includes/minishell.h"


void	ft_fill_lst(t_list **lst, t_parsing *parse, int start)
{
	t_list	*new;
	char	*str;

	str = ft_substr(parse->input, start, parse->len);
	if (parse->quote_to_del > 0)
		ft_strdel_quotes(parse, str);
	new = ft_lstnew(str);
	ft_lstadd_back(lst, new);
}
