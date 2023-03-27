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
			ft_print_sorted_env(parse);
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
		tmp = tmp->next;
	}
}
