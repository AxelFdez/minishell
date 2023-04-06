#include "../includes/minishell.h"

void	del_parsed_cmd(t_parsing *parse)
{
	int	i;

	i = 0;
	if (parse->built_in_cmd > 0)
	{
		while (i < parse->lst_target + 1)
		{
			parse->built_in_cmd = 0;
			ft_lstdel_front(&parse->lst_cmdline);
			i++;
		}
	}
}

void	pipe_child(t_parsing *parse, int pfd[2], int pipe_temp, int dup)
{
	if (parse->redirection_out == 0)
		dup2(pfd[1], STDOUT_FILENO);
	if (dup == 2)
		dup2(pipe_temp, STDIN_FILENO);
	close(pfd[0]);
	if (parse->built_in_cmd > 0)
		execute_built_in(parse);;
	execve(parse->command[0], parse->command, parse->env);
	// printf("minishell: ");
	// perror(parse->command[0]);
}

void	print_list(t_list *lst)
{
	if (!lst)
	{
		ft_printf("la liste est vide\n");
		return ;
	}
	while (lst != NULL)
	{
		ft_printf("[%s] ", lst->str);
		lst = lst->next;
	}
	ft_printf("\n");
}