#include "../includes/minishell.h"

void	ft_fill_lst(t_list **lst, t_parsing *parse, int start)
{
	t_list	*new;
	char	*str;

	str = NULL;
	if (parse->str_tmp)
	{
		str = ft_strdup(parse->str_tmp);
		free(parse->str_tmp);
		parse->str_tmp = NULL;
		str = ft_strjoin_free_s1_s2(str,
				ft_substr(parse->input, start, parse->len));
	}
	else
	{
		str = ft_substr(parse->input, start, parse->len);
		if (ft_strlen(str) == 0)
		{
			free(str);
			return ;
		}
	}
	if (parse->quote_to_del > 0)
	{
		ft_strdel_quotes(parse, str);
		parse->quote_to_del = 0;
	}
	if (str)
	{
		new = ft_lstnew(ft_strdup(str));
		ft_lstadd_back(lst, new);
		free(str);
	}
}
