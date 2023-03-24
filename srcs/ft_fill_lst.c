#include "../includes/minishell.h"


void	ft_fill_lst(t_list **lst, t_parsing *parse, int start)
{
	t_list	*new;
	char	*str;

	str = NULL;

	if (parse->str_tmp != NULL)
	{
		str = ft_strdup(parse->str_tmp);
		str = ft_strjoin(str, ft_substr(parse->input, start, parse->len));
		// free(parse->str_tmp);
		parse->str_tmp = NULL;
	}
	else // 
	{
		str = ft_substr(parse->input, start, parse->len);
		// printf("str = %s\n", str);

	}

	if (parse->quote_to_del > 0)
		ft_strdel_quotes(parse, str);
	if (ft_strlen(str) > 0)
	{
		new = ft_lstnew(str);
		ft_lstadd_back(lst, new);
	}

}
