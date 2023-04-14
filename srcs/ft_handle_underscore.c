#include "../includes/minishell.h"

static char	*ft_return_node_before(t_list *lst)
{
	t_list  *tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->str, ">>") == 0 || ft_strcmp(tmp->str, ">") == 0)
			return (tmp->prev->str);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_replace_underscore_value(t_list *lst, char *s)
{
	t_list	*tmp;
	char	*new;

	tmp = lst;
	new = "_=";
	while (tmp)
	{
		if (ft_strncmp(tmp->str, "_=", 2) == 0)
		{
			new = ft_strjoin(new, s);
			free(tmp->str);
			tmp->str = ft_strdup(new);
			free(new);
		}
		tmp = tmp->next;
	}
}

static void	ft_handle_under_export(t_parsing *parse)
{
	char	*str;

	str = ft_strdup(ft_lstlast(parse->lst_cmdline)->str);
	str[ft_str_chr(str, '=')] = '\0';
	ft_replace_underscore_value(parse->lst_env, str);
	free(str);
}

void	ft_handle_underscore(t_parsing *parse)
{

	if (ft_lst_strcmp(parse->lst_cmdline, "|") == 1
		|| ft_lst_strcmp(parse->lst_cmdline, "<") == 1
		|| ft_lst_strcmp(parse->lst_cmdline, "<<") == 1)
		ft_replace_underscore_value(parse->lst_env, "");
	else if (parse->lst_cmdline
		&& ft_strcmp(parse->lst_cmdline->str, "env") == 0)
		ft_replace_underscore_value(parse->lst_env, "/usr/bin/env");
	else if (ft_lst_strcmp(parse->lst_cmdline, ">>") == 1
		|| ft_lst_strcmp(parse->lst_cmdline, ">") == 1)
		ft_replace_underscore_value(parse->lst_env,
			ft_return_node_before(parse->lst_cmdline));
	else if (parse->lst_cmdline && ft_strcmp(parse->lst_cmdline->str,
			"export") == 0 && parse->lst_cmdline->next)
		ft_handle_under_export(parse);
	else
		ft_replace_underscore_value(parse->lst_env,
			ft_lstlast(parse->lst_cmdline)->str);
}
