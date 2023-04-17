#include "../../includes/minishell.h"

void	execute_built_in(t_parsing *parse)
{
	if (parse->built_in_cmd == 1)
		parse->ret_value = ft_env(parse);
	// else if (parse->built_in_cmd == 2)
	// 	parse->ret_value = ft_export(parse);
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
	exit(EXIT_SUCCESS);
}
