#include "../../includes/minishell.h"

void	ft_check_built_in(t_parsing *parse)
{
	t_list	*tmp;

	tmp = parse->lst_cmdline;
	while (tmp)
	{
		if ((ft_strcmp(tmp->str, "env") == 0 || ft_strcmp(tmp->str, "ENV") == 0) && (tmp->next == NULL))
			ft_env(parse);
		if (ft_strcmp(tmp->str, "export") == 0 && tmp->next == NULL)
			ft_export(parse);
		if ((ft_strcmp(tmp->str, "pwd") == 0 || ft_strcmp(tmp->str, "PWD") == 0) && (tmp->next == NULL))
			ft_pwd(parse);
		if (ft_strcmp(tmp->str, "echo") == 0 && ft_strcmp(tmp->next->str, "-n") == 0)
		{
			tmp = tmp->next;
			ft_echo(tmp, parse, 0);
		}
		if (ft_strcmp(tmp->str, "echo") == 0 && ft_strcmp(tmp->next->str, "-n") != 0)
			ft_echo(tmp, parse, 1);
		tmp = tmp->next;
	}
}
