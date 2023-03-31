#include "../../includes/minishell.h"

static void	ft_replace_value(t_list **lst)
{
	t_list	*tmp;
	char	*strtmp;
	
	tmp = *lst;
	while (tmp)
	{
		if (tmp->str[0] == '$')
		{
			strtmp = getenv(tmp->str +1);
			if (strtmp)
			{
				free(tmp->str);
				tmp->str = ft_strdup(strtmp);
			}
			else
				ft_lstdel_actual(lst, tmp);
		}
		tmp = tmp->next;
	}
}

static void	ft_fill_tmplst(t_parsing *parse, t_list **lst, int start, int len)
{
	t_list	*new;
	new = ft_lstnew(ft_substr(parse->str_tmp, start, len));
	ft_lstadd_back(lst, new);
}

static void	ft_loop(t_parsing *parse, t_list **lst)
{
	int	i = 0;
	int	len = 0;
	while (parse->str_tmp[i])
	{
		if (parse->str_tmp[i] == '$')
		{
			while (parse->str_tmp[i] && parse->str_tmp[i] != ' '
				&& parse->str_tmp[i] != '\"'
				&& parse->str_tmp[i] != '\'')
			{
				len++;
				i++;
			}
			ft_fill_tmplst(parse, lst, i - len, len);
			len = 0;
		}
		if (parse->str_tmp[i] != '$')
		{
			while (parse->str_tmp[i] && parse->str_tmp[i] != '$')
			{
				len++;
				i++;
			}
			ft_fill_tmplst(parse, lst, i - len, len);
			len = 0;
		}
	}
}

void	ft_handle_dollar_in_str(t_parsing *parse)
{
	t_list	*tmplst;
	t_list	*new;

	parse->str_tmp = ft_substr(parse->input, parse->i - parse->len, parse->len);
	tmplst = NULL;
	ft_loop(parse, &tmplst);
	ft_replace_value(&tmplst);
	free(parse->str_tmp);
	parse->str_tmp = ft_lst_to_str(tmplst);
	ft_strdel_quotes(parse, parse->str_tmp);
	new = ft_lstnew(ft_strdup(parse->str_tmp));
	ft_lstadd_back(&parse->lst_cmdline, new);
	parse->str_tmp = NULL;
	ft_lstdel_all(&tmplst);
}
