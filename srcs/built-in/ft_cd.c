#include "../../includes/minishell.h"

void	cd_in_cmdline(t_parsing *parse)
{
	if ((ft_strcmp(parse->lst_cmdline->str, "cd") == 0)
			|| (ft_strcmp(parse->lst_cmdline->str, "cd") == 0
			&& (ft_strcmp(parse->lst_cmdline->next->str, "~") == 0)))
	{
			if (ft_lst_strchr_pipe(parse->lst_cmdline) != 0)
			{
				parse->ret_value = ft_cd(parse);
				ft_lstdel_all(&parse->lst_cmdline);
			}
			else
			{
				while (ft_strcmp(parse->lst_cmdline->str, "|") != 0)
					ft_lstdel_front(&parse->lst_cmdline);
				ft_lstdel_front(&parse->lst_cmdline);
			}
			return ;
	}
}

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
