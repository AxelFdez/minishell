#include "../../includes/minishell.h"

static int	ft_var_is_exist(t_parsing *parse, t_list *tmp)
{
	t_list	*tmp_env;
	char	*s1;
	char	*s2;

	s1 = ft_set_str_to_comp(tmp->str);
	tmp_env = parse->lst_env;
	while (tmp_env)
	{
		s2 = ft_set_str_to_comp(tmp_env->str);
		if (ft_strcmp(s1, s2) == 0)
		{
			free(tmp_env->str);
			tmp_env->str = ft_strdup(tmp->str);
			free(s1);
			free(s2);
			return (1);
		}
		free(s2);
		tmp_env = tmp_env->next;
	}
	free(s1);
	return (0);
}

static int	ft_check_var_syntax(char *s)
{
	int		i;
	char	*var;

	if ((ft_strlen(s) == 0) || (s[0] >= '0' && s[0] <= '9'))
		return (0);
	var = ft_strdup(s);
	if (ft_strchr(var, '='))
		var[ft_str_chr(var, '=')] = '\0';
	i = 0;
	while (var[i])
	{
		if (ft_isalnum(var[i]) || var[i] == '_')
			i++;
		else
		{
			free(var);
			return (0);
		}
	}
	free(var);
	return (1);
}

static int	ft_new_var(t_parsing *parse, t_list *tmp)
{
	int		error;
	t_list	*new;

	error = 0;
	while (tmp)
	{
		if (ft_check_var_syntax(tmp->str))
		{
			if (ft_var_is_exist(parse, tmp) == 0)
			{
				new = ft_lstnew(ft_strdup(tmp->str));
				ft_lstadd_back(&parse->lst_env, new);
			}
		}
		else
		{
			ft_printf("export: `%s': not a valid identifier\n", tmp->str);
			error++;
		}
		tmp = tmp->next;
	}
	if (error > 0)
		return (1);
	return (0);
}

int	ft_export(t_parsing *parse)
{
	ft_lstprint_from_head(parse->lst_cmdline);
	t_list	*tmp;

	tmp = parse->lst_cmdline->next;
	if (tmp == NULL)
	{
		ft_print_export(parse);
		return (0);
	}
	return (ft_new_var(parse, tmp));
}
