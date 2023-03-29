#include "../../includes/minishell.h"


// static int	ft_var_is_exist(t_parsing *parse, t_list *tmp)
// {

// 	t_list	*tmp_env;

// 	tmp_env = parse->lst_env;
// 	while (tmp_env)
// 	{
		
// 		if (!ft_strncmp(tmp->str, tmp_env->str, ft_strlen(tmp_env->str)))
// 		{puts("AAAA");
			
// 			return (1);
// 		}
// 		tmp_env = tmp_env->next;
// 	}
// 	return (0);
// }


static int	ft_var_is_exist(t_parsing *parse, t_list *tmp)
{puts("in ft_var is exist");
	t_list	*tmp_env;
	char	*s1;
	char	*s2;

	s1 = ft_strdup(tmp->str);
	if (strchr(s1, '='))
		s1[ft_str_chr(s1, '=')] = '\0';
	tmp_env = parse->lst_env;
	while (tmp_env)
	{
		s2 = ft_strdup(tmp_env->str);
		if (strchr(s2, '='))
			s2[ft_str_chr(s2, '=')] = '\0';
		if (ft_strcmp(s1, s2) == 0)
		{puts("MOD VAR");
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

static void	ft_add_var(t_parsing *parse, t_list *tmp)
{
	puts("in ft_add_var");
	t_list	*new;


	new = ft_lstnew(ft_strdup(tmp->str));
	ft_lstadd_back(&parse->lst_env, new);
}

static int	ft_check_var_syntax(char *s)
{puts("in ft_check var syntax");
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isalnum(s[i]) || s[i] == '_'
				|| s[i] == '=' || s[i] == ' ' || s[i] == '\n')
			i++;
		else
			return (0);
	}
	return (1);
}

static int	ft_new_var(t_parsing *parse, t_list *tmp)
{puts("in ft_new_var");
	int	error;

	error = 0;
	while (tmp)
	{
		if (ft_check_var_syntax(tmp->str))
		{
			if (ft_var_is_exist(parse, tmp) == 0)
				ft_add_var(parse, tmp);
		}
		else
		{
			ft_printf("export: `%s' : not a valid identifier\n", tmp->str);
			error++;
		}
		tmp = tmp->next;
	}
	if (error > 0)
		return (1);
	return (0);
}

int	ft_export(t_parsing *parse)
{puts("in ft_export");
	int		error;
	t_list	*tmp;

	error = 0;
	tmp = parse->lst_cmdline->next;
	if (tmp == NULL)
	{
		ft_print_export(parse);
		return (0);
	}
	else
		return (ft_new_var(parse, tmp));
	// {
	// 	// while (tmp)
	// 	// {
	// 	// 	if (ft_check_var_syntax(tmp->str))
	// 	// 	{
	// 	// 		if (!ft_var_is_exist(parse, tmp))
	// 	// 			ft_add_var(parse, tmp);
	// 	// 		else
	// 	// 		{

	// 	// 		}
	// 	// 	}
	// 	// 	else
	// 	// 	{
	// 	// 		ft_printf("export: `%s' : not a valid identifier\n", tmp->str);
	// 	// 		error++;
	// 	// 	}
	// 	// 	tmp = tmp->next;
	// 	// }
	// }
	// if (error > 0)
	// 	return (1);
	// return (0);
}
