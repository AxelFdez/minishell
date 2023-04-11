#include "../../includes/minishell.h"

char	*ft_loop_tild_hyphen(t_parsing *parse, char c)
{
	t_list	*tmp;
	char	*ret;

	ret = NULL;
	tmp = parse->lst_env;
	while (tmp)
	{
		if (c == '~' && ft_strncmp(tmp->str, "HOME=", 5) == 0)
			ret = ft_strdup(tmp->str +5);
		if (c == '-' && ft_strncmp(tmp->str, "OLDPWD=", 7) == 0)
		{
			ret = ft_strdup(tmp->str +7);
			ft_printf("%s\n", ret);
		}
		tmp = tmp->next;
	}
	return (ret);
}

void	ft_update_oldpwd(t_parsing *parse, char *cwd)
{
	t_list	*tmp;
	char	*old_tmp;

	old_tmp = NULL;
	tmp = parse->lst_env;
	while (tmp)
	{
		if (ft_strnstr(tmp->str, "OLDPWD", 6))
		{
			old_tmp = ft_strdup(tmp->str);
			old_tmp[ft_str_chr(old_tmp, '=') + 1] = '\0';
			free(tmp->str);
			tmp->str = ft_strjoin(old_tmp, cwd);
			free(old_tmp);
		}
		tmp = tmp->next;
	}
}

void	ft_update_pwd(t_parsing *parse, char *cwd)
{
	t_list	*tmp;
	char	*pwd_tmp;

	pwd_tmp = NULL;
	tmp = parse->lst_env;
	while (tmp)
	{
		if (ft_strnstr(tmp->str, "PWD", 3))
		{
			pwd_tmp = ft_strdup(tmp->str);
			pwd_tmp[ft_str_chr(pwd_tmp, '=') + 1] = '\0';
			free(tmp->str);
			tmp->str = ft_strjoin(pwd_tmp, cwd);
			free(pwd_tmp);
		}
		tmp = tmp->next;
	}
}
