#include "../../includes/minishell.h"

static char	*ft_found_var(t_parsing *parse, char *s)
{
	t_list	*tmp;
	char	*ret;

	tmp = parse->lst_env;
	while (tmp)
	{
		if (s[0] == '$' && s[1] == '?')
		{
			ret = ft_strdup(ft_itoa(parse->tmp_ret_value));
			return (ret);
		}
		if (ft_strnstr(tmp->str, s +1, ft_strlen(s)))
		{
			ret = ft_strdup(tmp->str + ft_strlen(s));
			return (ret);
		}
		tmp = tmp->next;
	}
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

static void	ft_fill_tmplst(t_parsing *parse, t_list **lst, int start)
{
	t_list	*new;

	new = ft_lstnew(ft_substr(parse->str_tmp, start, parse->len_b));
	ft_lstadd_back(lst, new);
	parse->len_b = 0;
}

static void	ft_loop(t_parsing *parse, t_list **lst)
{
	while (parse->str_tmp[parse->i_b])
	{
		if (parse->str_tmp[parse->i_b] == '$')
		{
			while (parse->str_tmp[parse->i_b]
				&& parse->str_tmp[parse->i_b] != ' '
				&& parse->str_tmp[parse->i_b] != '\"'
				&& parse->str_tmp[parse->i_b] != '\'')
			{
				parse->len_b++;
				parse->i_b++;
			}
			ft_fill_tmplst(parse, lst, parse->i_b - parse->len_b);
		}
		if (parse->str_tmp[parse->i_b] != '$')
		{
			while (parse->str_tmp[parse->i_b]
				&& parse->str_tmp[parse->i_b] != '$')
			{
				parse->len_b++;
				parse->i_b++;
			}
			ft_fill_tmplst(parse, lst, parse->i_b - parse->len_b);
		}
	}
}

void	ft_handle_dollar_in_str(t_parsing *parse)
{
	t_list	*tmplst;
	t_list	*new;

	parse->len_b = 0;
	parse->i_b = 0;
	parse->str_tmp = ft_substr(parse->input, parse->i - parse->len, parse->len);
	printf("str_tmp = %s\n", parse->str_tmp);
	tmplst = NULL;
	ft_loop(parse, &tmplst);
	puts("tmplst = ");
	ft_lstprint_from_head(tmplst);
	ft_replace_value(parse, &tmplst);
	free(parse->str_tmp);
	parse->str_tmp = ft_lst_to_str(tmplst);
	ft_strdel_quotes(parse, parse->str_tmp);
	new = ft_lstnew(ft_strdup(parse->str_tmp));
	ft_lstadd_back(&parse->lst_cmdline, new);
	parse->str_tmp = NULL;
	ft_lstdel_all(&tmplst);
}
