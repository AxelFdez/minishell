#include "../../includes/minishell.h"

void	execute_built_in(t_parsing *parse)
{
	t_list	*tmp;
	int i;

	tmp = parse->lst_cmdline;
	while (tmp)
	{
		i = 0;
		if (parse->built_in_cmd == 1)
		{
			parse->ret_value = ft_env(parse);
			while (i < parse->lst_target + 1)
			{
				ft_lstdel_front(&parse->lst_cmdline);
				i++;
			}
			exit(EXIT_SUCCESS);
		}
		if (parse->built_in_cmd == 2)
		{
			if (parse->last_pipe == 0)
				parse->ret_value = ft_export(parse);
			while (i < parse->lst_target)
			{
				ft_lstdel_front(&parse->lst_cmdline);
				i++;
			}
			parse->last_pipe = 0;
			exit(EXIT_SUCCESS);
		}
		if (parse->built_in_cmd == 3)
		{
			parse->ret_value = ft_pwd();
			while (i < parse->lst_target + 1)
			{
				ft_lstdel_front(&parse->lst_cmdline);
				i++;
			}
			exit(EXIT_SUCCESS);
		}
		if (parse->built_in_cmd == 4)
		{
			ft_echo(tmp, parse);
			while (i < parse->lst_target)
			{
				ft_lstdel_front(&parse->lst_cmdline);
				i++;
			}
			exit(EXIT_SUCCESS);
		}
		if (parse->built_in_cmd == 5)
		{
			ft_unset(parse);
			while (i < parse->lst_target)
			{
				ft_lstdel_front(&parse->lst_cmdline);
				i++;
			}
			exit(EXIT_SUCCESS);
		}
		if (parse->built_in_cmd == 6)
		{
			parse->ret_value = ft_cd(parse);
			while (i < parse->lst_target)
			{
				ft_lstdel_front(&parse->lst_cmdline);
				i++;
			}
			exit(EXIT_SUCCESS);
		}
		if (parse->built_in_cmd == 7)
		{
			ft_exit(parse);
			while (i < parse->lst_target)
			{
				ft_lstdel_front(&parse->lst_cmdline);
				i++;
			}
			exit(EXIT_SUCCESS);
		}
	// { puts("check built in");
	// { puts("check built in");
	// 	if ((ft_strcmp(tmp->str, "env") == 0 || ft_strcmp(tmp->str, "ENV") == 0))
	// 		parse->ret_value = ft_env(parse);
	// 	if (ft_strcmp(tmp->str, "export") == 0)
	// 		parse->ret_value = ft_export(parse);
	// 	if (ft_strcmp(tmp->str, "unset") == 0)
	// 		ft_unset(parse);
	// 	if ((ft_strcmp(tmp->str, "pwd") == 0 || ft_strcmp(tmp->str, "PWD") == 0) && (tmp->next == NULL))
	// 		parse->ret_value = ft_pwd();
	// 	if (ft_strcmp(tmp->str, "echo") == 0)
	// 		ft_echo(tmp, parse);
	// 	if ((ft_strcmp(tmp->str, "cd") == 0) || (ft_strcmp(tmp->str, "cd") == 0 && (ft_strcmp(tmp->next->str, "~") == 0)))
	// 		parse->ret_value = ft_cd(parse);
	// 	if (ft_strcmp(tmp->str, "exit") == 0)
	// 		ft_exit(parse);
		tmp = tmp->next;
	}
}
