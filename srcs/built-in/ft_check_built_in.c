#include "../../includes/minishell.h"

void	execute_built_in(t_parsing *parse)
{
	int i;

	if (parse->built_in_cmd == 1)
		parse->ret_value = ft_env(parse);
	else if (parse->built_in_cmd == 2)
		parse->ret_value = ft_export(parse);
	else if (parse->built_in_cmd == 3)
		parse->ret_value = ft_pwd();
	else if (parse->built_in_cmd == 4)
		ft_echo(parse->lst_cmdline, parse);
	else if (parse->built_in_cmd == 5)
		ft_unset(parse);
	else if (parse->built_in_cmd == 6)
		parse->ret_value = ft_cd(parse);
	else if (parse->built_in_cmd == 7)
		ft_exit(parse);
	else if (parse->built_in_cmd == 8)
		ft_print_history(parse);
	i = 0;
	while (i < parse->lst_target + 1)
		{
			ft_lstdel_front(&parse->lst_cmdline);
			i++;
		}
	exit(EXIT_SUCCESS);
}
