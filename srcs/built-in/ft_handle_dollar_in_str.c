#include "../../includes/minishell.h"

static char	*ft_found_var(t_parsing *parse, char *s)
{
	t_list	*tmp;
	char	*ret;

	tmp = parse->lst_env;
	parse->s1 = ft_strdup(s +1);
	while (tmp)
	{
		if (s[0] == '$' && s[1] == '?')
		{
			ret = ft_strdup(ft_itoa(parse->tmp_ret_value));
			return (ret);
		}
		parse->s2 = ft_set_str_to_comp(tmp->str);
		if (ft_strcmp(parse->s1, parse->s2) == 0)
		{
			ret = ft_strdup(tmp->str + ft_strlen(s));
			free(parse->s1);
			free(parse->s2);
			return (ret);
		}
		tmp = tmp->next;
		free(parse->s2);
	}
	free(parse->s1);
	return (NULL);
}

static void	ft_replace_value(t_parsing *parse, t_list **lst)
{
	t_list	*tmp;
	char	*ret_var_name;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->str[0] == '$')
		{
			ret_var_name = ft_found_var(parse, tmp->str);
			if (ret_var_name)
			{
				free(tmp->str);
				tmp->str = ft_strdup(ret_var_name);
				free(ret_var_name);
			}
			else
				ft_lstdel_actual(lst, tmp);
		}
		tmp = tmp->next;
	}
}

void	ft_handle_dollar_in_str(t_parsing *parse)
{
	t_list	*tmplst;
	t_list	*new;

	parse->len_b = 0;
	parse->i_b = 0;
	parse->str_tmp = ft_substr(parse->input, parse->i - parse->len,
			parse->len);
	tmplst = NULL;
	ft_loop(parse, &tmplst);
	ft_replace_value(parse, &tmplst);
	free(parse->str_tmp);
	parse->str_tmp = NULL;
	if (ft_lstsize(tmplst) > 2)
	{
		parse->str_tmp = ft_lst_to_str(tmplst);
		ft_strdel_quotes(parse, parse->str_tmp);
		new = ft_lstnew(ft_strdup(parse->str_tmp));
		ft_lstadd_back(&parse->lst_cmdline, new);
	}
	free(parse->str_tmp);

	parse->str_tmp = NULL;
	ft_lstdel_all(&tmplst);
}
