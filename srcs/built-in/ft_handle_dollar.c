#include "../../includes/minishell.h"

static void	ft_found_var(t_parsing*parse)
{
	t_list	*tmp;

	tmp = parse->lst_env;
	while (tmp)
	{
		if (ft_strnstr(tmp->str, parse->var_name +1,
				ft_strlen(parse->var_name)))
		{puts("AAAAA");
			parse->str_tmp = ft_strjoin(parse->str_tmp,
					tmp->str + ft_strlen(parse->var_name));
			break ;
		}
		tmp = tmp->next;
	}
}

void	ft_handle_dollar_in_str(t_parsing *parse)
{
	int		i;

	i = 0;
	if (parse->len > 0)
		parse->str_tmp = ft_substr(parse->input,
				parse->i - parse->len, parse->len);
	else
		(parse->str_tmp = "");
	while (parse->input[parse->i] && parse->input[parse->i] != '\"'
		&& parse->input[parse->i] != '\'' && parse->input[parse->i] != ' ')
	{
		parse->var_name[i] = parse->input[parse->i];
		i++;
		parse->i++;
	}
	ft_found_var(parse);
	parse->var_name[0] = '\0';
}
