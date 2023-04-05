#include "../../includes/minishell.h"

static void	ft_update_oldpwd(t_parsing *parse, char *cwd)
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

static void	ft_update_pwd(t_parsing *parse, char *cwd)
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

static void	ft_found_home(t_parsing *parse)
{
	t_list	*tmp;
	char	*ret;

	ret = NULL;
	tmp = parse->lst_env;
	while (tmp)
	{
		if (ft_strnstr(tmp->str, "HOME", 4))
			ret = ft_strdup(tmp->str +5);
		tmp = tmp->next;
	}
	if (chdir(ret) != 0)
	{
		perror("cd: ");
		free(ret);
		return ;
	}
	free(ret);
}

static char	*ft_get_current_position(void)
{
	char	*cwd;
	char	buffer[4096];


	cwd = getcwd(buffer, sizeof(buffer));
	if (!cwd)
	{
		perror("getcwd");
		return (NULL);
	}
	return (cwd);
}

int	ft_cd(t_parsing *parse)
{
	t_list	*tmp;
	char	*cwd;

	tmp = parse->lst_cmdline;
	cwd = ft_get_current_position();
	ft_update_oldpwd(parse, cwd);
	if (tmp->next == NULL || ft_strcmp(tmp->next->str, "~") == 0)
		ft_found_home(parse);
	else if (chdir(tmp->next->str) != 0)
	{
		write (2, "cd: ", 4);
		perror(tmp->next->str);
		return (1);
	}
	cwd = ft_get_current_position();
	ft_update_pwd(parse, cwd);
	return (0);
}
