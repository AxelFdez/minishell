#include "../../includes/minishell.h"

// char	*ft_loop_tild_hyphen(t_parsing *parse, char c)
// {
// 	t_list	*tmp;
// 	char	*ret;
// 	ret = NULL;
// 	tmp = parse->lst_env;
// 	while (tmp)
// 	{
// 		if (c == '~' && ft_strncmp(tmp->str, "HOME=", 5) == 0)
// 			ret = ft_strdup(tmp->str +5);
// 		if (c == '-' && ft_strncmp(tmp->str, "OLDPWD=", 7) == 0)
// 		{
// 			ret = ft_strdup(tmp->str +7);
// 			ft_printf("%s\n", ret);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (ret);
// }

static int	ft_handle_tild_hyphen(t_parsing *parse, char c)
{
	char	*ret;

	ret = NULL;
	ret = ft_loop_tild_hyphen(parse, c);
	if (c == '~' && !ret)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (chdir(ret) != 0)
	{
		perror("cd: ");
		free(ret);
		return (1);
	}
	free(ret);
	return (0);
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
	int		ret;

	ret = 0;
	tmp = parse->lst_cmdline;
	cwd = ft_get_current_position();
	if (tmp->next == NULL || ft_strcmp(tmp->next->str, "~") == 0)
		ret = ft_handle_tild_hyphen(parse, '~');
	else if (tmp->next == NULL || ft_strcmp(tmp->next->str, "-") == 0)
		ret = ft_handle_tild_hyphen(parse, '-');
	else if (chdir(tmp->next->str) != 0)
	{
		write (2, "cd: ", 4);
		perror(tmp->next->str);
		return (1);
	}
	ft_update_oldpwd(parse, cwd);
	cwd = ft_get_current_position();
	ft_update_pwd(parse, cwd);
	return (ret);
}
