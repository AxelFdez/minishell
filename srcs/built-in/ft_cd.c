#include "../../includes/minishell.h"

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

char	*ft_get_current_position(void)
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
	ft_strcpy(parse->pwd_save, cwd);
	printf("save PWD = %s\n", parse->pwd_save);
	
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
