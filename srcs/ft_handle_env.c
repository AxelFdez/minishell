#include "../includes/minishell.h"

static char	*ft_increment_shlvl(char *s)
{
	int		lvl;
	int		i;
	char	*ret;
	char	*ret_itoa;

	lvl = ft_atoi(s +6);
	lvl++;
	ret_itoa = ft_itoa(lvl);
	i = 0;
	while (s[i++])
		if (s[i] == '=')
			s[i +1] = '\0';
	ret = ft_strdup(s);
	ret = ft_strjoin_free_s1(ret, ret_itoa);
	free(ret_itoa);
	return (ret);
}

static void	ft_handle_oldpwd(t_parsing *parse)
{
	t_list	*tmp;

	tmp = parse->lst_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->str, "OLDPWD=", 7) == 0)
			ft_lstdel_actual(&parse->lst_env, tmp);
		
		tmp = tmp->next;
	}
	ft_lstadd_back(&parse->lst_env, ft_lstnew(ft_strdup("OLDPWD")));
}

static void	ft_create_env(t_parsing *parse)
{
	int		i;
	t_list	*new;
	char	*var_to_create[5];
	
	

	var_to_create[0] = "OLDPWD";
	var_to_create[1] = "PWD=";
	var_to_create[2] = "SHLVL=1";
	var_to_create[3] = "_=";
	var_to_create[4] = NULL;

	var_to_create[1] = ft_strjoin(var_to_create[1], ft_get_current_position());
	
	i = 0;
	parse->lst_env = NULL;
	while (var_to_create[i])
	{
		new = ft_lstnew(ft_strdup(var_to_create[i]));
		ft_lstadd_back(&parse->lst_env, new);
		i++;
	}
	free(var_to_create[1]);

	ft_lstprint_from_head(parse->lst_env);
}


void	ft_retrieve_env(t_parsing *parse, char **env)
{
	int		i;
	t_list	*new;
	char	*lvl;
	if (!*env)
	{
		ft_create_env(parse);
		return ;
	}
	parse->lst_env = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "SHLVL", 5))
		{
			lvl = ft_increment_shlvl(env[i]);
			new = ft_lstnew(ft_strdup(lvl));
			ft_lstadd_back(&parse->lst_env, new);
			free(lvl);
		}
		else
		{
			new = ft_lstnew(ft_strdup(env[i]));
			ft_lstadd_back(&parse->lst_env, new);
		}
		i++;
	}
	ft_handle_oldpwd(parse);
}

char	**ft_lst_env_to_tab(t_list *lst)
{
	t_list	*tmp;
	char	**array;
	int		i;

	i = 0;
	tmp = lst;
	array = malloc(sizeof (char *) * (ft_lstsize(lst) + 1));
	while (tmp)
	{
		if (ft_found_char(tmp->str, '=') == 1)
		{
			array[i] = ft_strdup(tmp->str);
		i++;
		}
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}
