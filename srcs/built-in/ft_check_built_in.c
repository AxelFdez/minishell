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
			ft_env(parse);
			while (i < parse->lst_target + 1)
			{
				ft_lstdel_front(&parse->lst_cmdline);
				i++;
			}
			exit(EXIT_SUCCESS);
		}
		if (parse->built_in_cmd == 2)
		{
			//ft_print_sorted_env(parse);
			while (i < parse->lst_target)
			{
				ft_lstdel_front(&parse->lst_cmdline);
				i++;
			}
			exit(EXIT_SUCCESS);
		}
		//printf("temp = %s\n",tmp->str);
		if (parse->built_in_cmd == 3)
		{
			ft_pwd();
			while (i < parse->lst_target + 1)
			{
				free(parse->lst_cmdline->str);
				ft_lstdel_front(&parse->lst_cmdline);
				i++;
			}
			//printf("target = %d\n", parse->lst_target);
			//ft_lstprint_from_head(parse->lst_cmdline);

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
