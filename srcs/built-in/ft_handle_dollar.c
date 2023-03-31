#include "../../includes/minishell.h"

static void	ft_found_var(t_parsing *parse)
{
	t_list	*tmp;

	tmp = parse->lst_env;
	while (tmp)
	{
		if (ft_strnstr(tmp->str, parse->var_name +1,
				ft_strlen(parse->var_name)))
		{
			parse->str_tmp = ft_strjoin_free_s1(parse->str_tmp,
					tmp->str + ft_strlen(parse->var_name));
			
				
			break ;
		}
		tmp = tmp->next;
	}
}

static void	ft_retrieve_var_name(t_parsing *parse)
{
	int	i;
	i = 0;
	while (parse->input[parse->i] && parse->input[parse->i] != '\"'
		&& parse->input[parse->i] != '\'' && parse->input[parse->i] != ' ')
	{
		parse->var_name[i] = parse->input[parse->i];
		i++;
		parse->i++;
		// parse->len++;
	}
	parse->var_name[i] = '\0';
	ft_found_var(parse);
	ft_bzero(parse->var_name, 1024);
}

void	ft_handle_dollar(t_parsing *parse)
{
	if (parse->len > 0)
		parse->str_tmp = ft_substr(parse->input,
				parse->i - parse->len, parse->len);
	else
		parse->str_tmp = ft_calloc(1, sizeof(char));
	if (parse->input[parse->i +1] == '?')
	{
		parse->str_tmp = ft_strjoin(parse->str_tmp,
				ft_itoa(parse->tmp_ret_value));
		parse->i += 2;
	}
	else
		ft_retrieve_var_name(parse);
}
