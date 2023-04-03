#include "../includes/minishell.h"


void	ft_fill_lst(t_list **lst, t_parsing *parse, int start)
{
	// printf("parse->str_tmp in fill lst = %s\n", parse->str_tmp);

	t_list	*new;
	char	*str;

	str = NULL;

	if (parse->str_tmp != NULL)
	{
		str = ft_strdup(parse->str_tmp);
		// printf("str from fill lst = %s\n", str);
		str = ft_strjoin_free_s1(str, ft_substr(parse->input, start, parse->len));
		// free(parse->str_tmp);
		parse->str_tmp = NULL;
	}
	else 
		str = ft_substr(parse->input, start, parse->len);
	if (parse->quote_to_del > 0)
	{
		ft_strdel_quotes(parse, str);
		parse->quote_to_del = 0;
	}
	new = ft_lstnew(str);
	ft_lstadd_back(lst, new);
}
