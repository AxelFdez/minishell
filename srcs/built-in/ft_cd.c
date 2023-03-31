#include "../../includes/minishell.h"

static char	*ft_found_home(t_parsing *parse)
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
	return (ret);
}

int	ft_cd(t_parsing *parse)
{
	t_list	*tmp;
	char	*ret;

	ret = NULL;
	tmp = parse->lst_cmdline;
	if (tmp->next == NULL || ft_strcmp(tmp->next->str, "~") == 0)
	{
		ret = ft_found_home(parse);
		if (chdir(ret) != 0)
		{
			perror("cd: ");
			free(ret);
			return (1);
		}
		free(ret);
	}
	else if (chdir(tmp->next->str) != 0)
	{
		write (2, "cd: ", 4);
		perror(tmp->next->str);
		return (1);
	}
	return (0);
}
