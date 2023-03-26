#include "../../includes/minishell.h"

void	ft_check_built_in(t_parsing *parse)
{
	t_list	*tmp;

	tmp = parse->lst_cmdline;
	while (tmp)
	{
		if ((ft_strcmp(tmp->str, "env") == 0 || ft_strcmp(tmp->str, "ENV") == 0) && (tmp->next == NULL))
			ft_env(parse);
		if (ft_strcmp(tmp->str, "export") == 0)
			ft_export(parse);
		if (ft_strcmp(tmp->str, "unset") == 0)
			ft_unset(parse);
		if ((ft_strcmp(tmp->str, "pwd") == 0 || ft_strcmp(tmp->str, "PWD") == 0) && (tmp->next == NULL))
			ft_pwd();
		if (ft_strcmp(tmp->str, "echo") == 0)
			ft_echo(tmp, parse);
		if (ft_strcmp(tmp->str, "cd") == 0)
			ft_cd(parse);
		tmp = tmp->next;
	}
}
