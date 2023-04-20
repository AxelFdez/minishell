#include "../../includes/minishell.h"

void	ft_fill_tmplst(t_parsing *parse, t_list **lst, int start)
{
	t_list	*new;

	new = ft_lstnew(ft_substr(parse->str_tmp, start, parse->len_b));
	ft_lstadd_back(lst, new);
	parse->len_b = 0;
}

char	*ft_set_str_to_comp(char *s)
{
	char	*s1;

	s1 = ft_strdup(s);
	if (ft_strchr(s1, '='))
		s1[ft_str_chr(s1, '=')] = '\0';
	return (s1);
}

static void	ft_is_dollar(t_parsing *parse, t_list **lst)
{puts("is dollar");
	while (parse->str_tmp[parse->i_b] && parse->str_tmp[parse->i_b] != ' '
			&& parse->str_tmp[parse->i_b] != '\"' && parse->str_tmp[parse->i_b]
			!= '\'' && parse->str_tmp[parse->i_b] != '\n'
			&& !ft_found_char(parse->non_bl_chars, parse->str_tmp[parse->i_b]))
	{
			parse->len_b++;
			parse->i_b++;
		if (parse->str_tmp[parse->i_b] == '?')
		{
			parse->len_b++;
			parse->i_b++;
			break ;
		}
		if (parse->str_tmp[parse->i_b] == '$')
			break ;
	}
	ft_fill_tmplst(parse, lst, parse->i_b - parse->len_b);
}

static void	ft_isnot_dollar(t_parsing *parse, t_list **lst)
{
	while (parse->str_tmp[parse->i_b] && parse->str_tmp[parse->i_b] != '$')
	{
		parse->len_b++;
		parse->i_b++;
	}
	ft_fill_tmplst(parse, lst, parse->i_b - parse->len_b);
}

void	ft_loop_dollar(t_parsing *parse, t_list **lst)
{
	while (parse->str_tmp[parse->i_b])
	{
		if (parse->str_tmp[parse->i_b] == '$')
			ft_is_dollar(parse, lst);
		else if (parse->str_tmp[parse->i_b] != '$')
			ft_isnot_dollar(parse, lst);
	}
	ft_lstprint_from_head(*lst);
}
