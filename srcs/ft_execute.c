
#include "../includes/minishell.h"

int ft_lst_strchr_pipe(t_list *list)
{
	t_list *temp;
	temp = list;

	while (temp)
	{
		if (ft_strcmp(temp->str, "|") == 0)
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
		|| ft_strcmp(tmp, "exit") == 0 || ft_strcmp(tmp, "history") == 0)
	{
		return (0);
	}
	return (1);
}

int	parsing_built_in(t_parsing *parse)
{
	t_list	*tmp;

	tmp = parse->lst_cmdline;
	parse->lst_target = 0;
	while (tmp && ft_strchr(tmp->str, '|') == NULL)
	{
		parse->lst_target++;
		tmp = tmp->next;
	}
	tmp = parse->lst_cmdline;
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
		if (ft_strcmp(tmp->str, "history") == 0)
			return (8);
		tmp = tmp->next;
	}
	return (0);
}

void	execute_built_in_alone(t_parsing *parse)
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
		check_herringbone(parse);
		parse->ret_value = ft_cd(parse);
	}
	ft_lstdel_all(&parse->lst_cmdline);
	return ;
}

void	built_in_used_alone(t_parsing *parse)
{
	int		built_in_found;

	built_in_found = 0;
	if (ft_lst_strchr_pipe(parse->lst_cmdline) == 0)
		return;
		if (ft_strcmp(parse->lst_cmdline->str, "export") == 0
			|| ft_strcmp(parse->lst_cmdline->str, "unset") == 0
			|| ft_strcmp(parse->lst_cmdline->str, "cd") == 0
			|| ft_strcmp(parse->lst_cmdline->str, "exit") == 0)
			built_in_found = 1;
	if (built_in_found == 1)
		execute_built_in_alone(parse);
}

void error_exec_message(t_parsing *parse)
{
	if (parse->command[0][0] == '/')
	{
		if (access(parse->command[0], F_OK))
			ft_printf("minishell: %s: no such file or directory\n",
				parse->command[0]);
		else
			ft_printf("minishell: %s: is a directory\n", parse->command[0]);
	}
	else
	ft_printf("minishell: %s: command not found\n", parse->command[0]);
}

void	check_heredoc(t_parsing *parse)
{
	parse->redirection_in = 0;
	while (check_herringbones_input(parse) == 0 && parse->lst_cmdline->str[0] != '|' && parse->lst_cmdline != NULL)
	{
		if (ft_strcmp(parse->lst_cmdline->str, "<<") == 0)
		{
			parse->redirection_in = 1;
			ft_heredoc(parse, &parse->lst_cmdline);
			if (!parse->lst_cmdline)
				return;
		}
		if (!parse->lst_cmdline || !parse->lst_cmdline->next || parse->lst_cmdline->str[0] == '|')
			break;
		if (ft_strcmp(parse->lst_cmdline->str, "<<") != 0)
			parse->lst_cmdline = parse->lst_cmdline->next;
	}
	while (parse->lst_cmdline->prev != NULL)
		parse->lst_cmdline = parse->lst_cmdline->prev;
}


void	simple_command(t_parsing *parse)
{
	pid_t child;

	check_heredoc(parse);
	if (!parse->lst_cmdline)
		return;
	child = fork();
	if (child < 0)
		perror("fork error\n");
	else if (child == 0)
	{
		parse->built_in_cmd = 0;
		check_herringbone(parse);
		if (check_builtin_input(parse) == 1)
			parsing_cmd(parse);
		else
			parse->built_in_cmd = parsing_built_in(parse);
		if (parse->heredoc_pfd > 0)
		{
			dup2(parse->heredoc_pfd, STDIN_FILENO);
			close(parse->heredoc_pfd);
		}
		if (parse->built_in_cmd > 0)
			execute_built_in(parse);
		execve(parse->command[0], parse->command, parse->env);
		error_exec_message(parse);
		exit(parse->ret_value);
	}
	waitpid(child, &parse->status, 0);
	parse->ret_value = parse->status / 256;
	if (parse->heredoc_pfd > 0)
	{
		close(parse->heredoc_pfd);
		dup2(parse->fd_stdin, STDIN_FILENO);
	}
}


void execute_cmd(t_parsing *parse)
{
	parse->status = 0;
	sig.heredoc = 0;
	built_in_used_alone(parse);
	//count_heredoc(parse);
	if (!parse->lst_cmdline)
		return ;
	sig.child = 0;
	if (ft_lst_strchr_pipe(parse->lst_cmdline) == 0)
		pipex(parse);
	else
		simple_command(parse);
	return;
}
