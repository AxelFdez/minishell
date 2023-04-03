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

void	ft_retrieve_env(t_parsing *parse, char **env)
{
	int		i;
	t_list	*new;
	char	*lvl;

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
}

char	**ft_lst_to_char_tab(t_list *lst)
{
	t_list	*tmp;
	char	**array;
	int		i;

	i = 0;
	tmp = lst;
	array = malloc(sizeof (char *) * (ft_lstsize(lst) + 1));
	while (tmp)
	{
		array[i] = ft_strdup(tmp->str);
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}
