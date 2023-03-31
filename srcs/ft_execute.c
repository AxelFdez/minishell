
#include "../includes/minishell.h"

int ft_lst_strchr_meta(t_list *list)
{
	t_list *temp;
	temp = list;

	while (temp)
	{
		if (ft_strchr(temp->str, '|') != NULL)
			return (0);
		else if (ft_strchr(temp->str, '>') != NULL)
			return (0);
		else if (ft_strchr(temp->str, '<') != NULL)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int ft_lst_strchr_pipe(t_list *list)
{
	t_list *temp;
	temp = list;

	while (temp)
	{
		if (ft_strchr(temp->str, '|') != NULL)
			return (0);
		temp = temp->next;
	}
	return (1);
}

int check_builtin_input(t_parsing *parse)
{
	char	*tmp;

	tmp = parse->lst_cmdline->str;
	if (ft_strcmp(tmp, "env") == 0 || ft_strcmp(tmp, "ENV") == 0
		|| ft_strcmp(tmp, "export") == 0 || ft_strcmp(tmp, "pwd") == 0
		|| ft_strcmp(tmp, "PWD") == 0 || ft_strcmp(tmp, "echo") == 0
		|| ft_strcmp(tmp, "unset") == 0 || ft_strcmp(tmp, "cd") == 0
		|| ((ft_strcmp(tmp, "cd") == 0 && (ft_strcmp(tmp, "~"))))
		|| ft_strcmp(tmp, "exit") == 0)
	{
		return (0);
	}
	return (1);
}

int	parsing_built_in(t_parsing *parse)
{
	t_list	*tmp;
	t_list	*tmp2;
	tmp = parse->lst_cmdline;
	tmp2 = parse->lst_cmdline;
	parse->lst_target = 0;

	while (tmp2 && ft_strchr(tmp2->str, '|') == NULL)
	{
		parse->lst_target++;
		tmp2 = tmp2->next;
	}
	while (tmp)
	{
		if (ft_strcmp(tmp->str, "env") == 0 || ft_strcmp(tmp->str, "ENV") == 0)
			return (1);
		if (ft_strcmp(tmp->str, "export") == 0)
			return (2);
		if (ft_strcmp(tmp->str, "pwd") == 0 || ft_strcmp(tmp->str, "PWD") == 0)
			return (3);
		if (ft_strcmp(tmp->str, "echo") == 0)
			return (4);
		if (ft_strcmp(tmp->str, "unset") == 0)
			return (5);
		if ((ft_strcmp(tmp->str, "cd") == 0) || (ft_strcmp(tmp->str, "cd") == 0 && (ft_strcmp(tmp->next->str, "~") == 0)))
			return (6);
		if (ft_strcmp(tmp->str, "exit") == 0)
			return (7);
		tmp = tmp->next;
	}
	return (0);
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
}

void	execute_built_in_first(t_parsing *parse)
{
	if (ft_strcmp(parse->lst_cmdline->str, "export") == 0
		&& ft_lst_strchr_pipe(parse->lst_cmdline) == 1)
		parse->ret_value = ft_export(parse);
	else if (ft_strcmp(parse->lst_cmdline->str, "unset") == 0)
		ft_unset(parse);
	else if (ft_strcmp(parse->lst_cmdline->str, "exit") == 0)
		ft_exit(parse);
	else if ((ft_strcmp(parse->lst_cmdline->str, "cd") == 0)
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

void	built_in_works(t_parsing *parse)
{
	t_list *temp;
	int		built_in_found;

	built_in_found = 0;
	temp = parse->lst_cmdline;
	if (ft_lst_strchr_pipe(parse->lst_cmdline) == 0)
		return;
	while (temp)
	{
		if (ft_strcmp(temp->str, "export") == 0
			|| ft_strcmp(temp->str, "unset") == 0
			|| ft_strcmp(temp->str, "cd") == 0
			|| (ft_strcmp(temp->str, "cd") == 0 && ft_strcmp(temp->next->str, "~") == 0)
			|| ft_strcmp(temp->str, "exit") == 0)
			built_in_found = 1;
		if (!temp->next)
			break;
		temp = temp->next;
	}
	if (built_in_found == 1)
		execute_built_in_first(parse);
}

void execute_cmd(t_parsing *parse)
{
	pid_t child;

	check_herringbone(parse);
	built_in_works(parse);
	//print_list(parse->lst_cmdline);
	// printf("bef = %p\n", parse->lst_cmdline->prev);
	// printf("ptr = %p\n", parse->lst_cmdline);
	// printf("str = %s\n", parse->lst_cmdline->str);
	// printf("aft = %p\n", parse->lst_cmdline->next);
	child = fork();
	if (child < 0)
		perror("fork error\n");
	else if (child == 0)
	{
		parse->built_in_cmd = 0;
		if (check_builtin_input(parse) == 1)
		{
			// puts("AAA");
			// exit(EXIT_SUCCESS);
			parsing_cmd(parse);
		}
		else
		{
			// puts("BBB");
			// exit(EXIT_SUCCESS);
			parse->built_in_cmd = parsing_built_in(parse);
		}
		//exit(EXIT_SUCCESS);
		if (ft_lst_strchr_pipe(parse->lst_cmdline) == 0)
			pipex(parse);
		if (parse->built_in_cmd > 0)
			execute_built_in(parse);
		execve(parse->command[0], parse->command, parse->env);
		perror("command not found");
	}
	wait(NULL);
	return ;
}

