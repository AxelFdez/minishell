#include "../../includes/minishell.h"


static int	ft_is_exist(t_parsing *parse, t_list *tmp)
{
	t_list	*tmp_env;

	tmp_env = parse->lst_env;
	while (tmp_env)
	{
		if (!ft_strncmp(tmp_env->str, tmp->str,
				ft_str_chr(tmp_env->str, '=')))
		{
			printf("tmp_env->str = %s\n", tmp_env->str);
			printf("tmp->str = %s\n", tmp->str);
			free(tmp_env->str);
			tmp_env->str = ft_strdup(tmp->str);
			return (1);
		}
		tmp_env = tmp_env->next;
	}
	return (0);
}


static void	ft_add_node(t_parsing *parse, t_list *tmp)
{
	t_list	*new;
	
	printf("tmp->str before if = %s\n", tmp->str);

	if(ft_is_exist(parse, tmp))
		puts("exist");
	else{

	new = ft_lstnew(ft_strdup(tmp->str));
	ft_lstadd_back(&parse->lst_env, new);
	}
}

int	ft_export(t_parsing *parse)
{
	size_t	i;
	int		error;
	// t_list	*new;
	t_list	*tmp;

	i = 0;
	error = 0;
	tmp = parse->lst_cmdline->next;
	if (tmp == NULL)
		ft_print_export(parse);
	else
	{
		while (tmp)
		{
			while (tmp->str[i] || ft_isalnum(tmp->str[i]) || tmp->str[i] == '_'
				|| tmp->str[i] == '=')
				i++;
			if (i == ft_strlen(tmp->str))
			{
				ft_add_node(parse, tmp);
				// new = ft_lstnew(ft_strdup(tmp->str));
				// ft_lstadd_back(&parse->lst_env, new);
			}
			else
			{
				ft_printf("export: `%s' : not a valid identifier\n", tmp->str);
				error++;
			}
			i = 0;
			tmp = tmp->next;
		}
	}
	if (error > 0)
		return (1);
	return (0);
}
