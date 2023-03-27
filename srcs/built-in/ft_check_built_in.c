#include "../../includes/minishell.h"

void	execute_built_in(t_parsing *parse)
{
	t_list	*tmp;
	t_list	*tmp2;
	int i;

	tmp = parse->lst_cmdline;
	tmp2 = parse->lst_cmdline;
	parse->lst_target = 0;
	while (tmp2 && ft_strchr(tmp2->str, '|') == NULL)
	{
		parse->lst_target++;
		tmp2 = tmp2->next;
	}
	printf("target = %d\n", parse->lst_target);
	// printf("1er node = %s\n", parse->lst_cmdline->str);
	// exit(EXIT_FAILURE);
	while (tmp)
	{
		if (ft_strcmp(tmp->str, "env") == 0 || ft_strcmp(tmp->str, "ENV") == 0)
		{
			ft_env(parse);
			i = 0;
			while (i < parse->lst_target + 1)
			{
				ft_lstdel_front(&parse->lst_cmdline);
				i++;
			}
			//ft_lstprint_from_head(parse->lst_cmdline);
			execve(0,0,0);
		}
		if (ft_strcmp(tmp->str, "export") == 0)
		{
			ft_print_sorted_env(parse);
			i = 0;
			while (i < parse->lst_target)
			{
				ft_lstdel_front(&parse->lst_cmdline);
				i++;
			}
			execve(0,0,0);
		}
		//printf("temp = %s\n",tmp->str);
		if (ft_strcmp(tmp->str, "pwd") == 0 || ft_strcmp(tmp->str, "PWD") == 0)
		{
			printf("BP\n");
			i = 0;
			ft_pwd();
			while (i < parse->lst_target + 1)
			{
				ft_lstdel_front(&parse->lst_cmdline);
				i++;
			}
			execve(0,0,0);
		}
		if (ft_strcmp(tmp->str, "echo") == 0)
		{
			ft_echo(tmp, parse);
			i = 0;
			while (i < parse->lst_target)
			{
				ft_lstdel_front(&parse->lst_cmdline);
				i++;
			}
			execve(0,0,0);
		}
		tmp = tmp->next;
	}
}
