#include "../../includes/minishell.h"

/*static void	ft_found_var(t_parsing *parse)
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
	puts("retrieve");
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
	printf("var_name = %s\n", parse->var_name);
	ft_found_var(parse);
	ft_bzero(parse->var_name, 1024);
}*/



void	ft_handle_dollar_in_str(t_parsing *parse)
{
	int		i;
	int		len;
	t_list	*tmplst;
	t_list	*new;

	// char	*tmp;

	parse->str_tmp = ft_substr(parse->input, parse->i - parse->len, parse->len);
	ft_strdel_quotes(parse, parse->str_tmp);
	printf("parse->str_tmp = %s\n", parse->str_tmp);
	i = 1;
	len = 0;
	tmplst = NULL;
	while (parse->str_tmp[i])
	{
		while (parse->str_tmp[i] && parse->str_tmp[i] != '$')
		{
			i++;
			len++;
		}

		if (parse->str_tmp[i] == '$' || parse->str_tmp[i] == '\"')
		{
			new = ft_lstnew(ft_substr(parse->str_tmp, i - len, len));
			ft_lstadd_back(&tmplst, new);
			len = 0;
			
			while (parse->str_tmp[i] != ' ' && parse->str_tmp[i] != '\"')
			{
				i++;
				len++;
			}
			new = ft_lstnew(ft_substr(parse->str_tmp, i - len, len));
			ft_lstadd_back(&tmplst, new);
			len = 0;
			i++;
		}
		else
		{
			i++;
			len++;
		}
	}
	ft_lstprint_from_head(tmplst);
	ft_lstdel_all(&tmplst);

	
}
