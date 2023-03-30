#include "../includes/minishell.h"

void	ft_lstdel_current(t_list **lst)
{
	if (!(*lst))
		return ;
	if ((*lst)->prev == NULL)
	{
		ft_lstdel_front(&(*lst));
		(*lst)->prev = NULL;
	}
	else if ((*lst)->next == NULL)
	{
		(*lst) = (*lst)->prev;
		ft_lstdel_back(&(*lst));
	}
	else
	{
		((*lst)->prev)->next = (*lst)->next;
		((*lst)->next)->prev = (*lst)->prev;
		free((*lst)->str);
		free((*lst));
		(*lst) = (*lst)->next;
	}
}


void	input_redirection(t_list **parse)
{
	int fd[1];
	ft_lstdel_current(&(*parse));
	if (access((*parse)->str, F_OK) != 0)
	{
		perror((*parse)->str);
		exit(EXIT_FAILURE);
	}
	if (access((*parse)->str, R_OK) != 0)
	{
		perror((*parse)->str);
		exit(EXIT_FAILURE);
	}
	fd[0] = open((*parse)->str, O_RDONLY);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	ft_lstdel_current(&(*parse));
}

void	output_redirection(t_list **parse)
{
	int fd;
	ft_lstdel_current(&(*parse));
	fd = open((*parse)->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror("fd error");
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_lstdel_current(&(*parse));
}

void	ft_append(t_list **parse)
{
	int fd[1];

	ft_lstdel_current(&(*parse));
	fd[0] = open((*parse)->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd[0] < 0)
		perror("fd error");
	dup2(fd[0], STDOUT_FILENO);
	close(fd[0]);
	ft_lstdel_current(&(*parse));
}


void	check_herringbone(t_parsing *parse)
{
	while (parse->lst_cmdline->next != NULL && parse->lst_cmdline->str[0] != '|')
	{
		if (ft_strcmp(parse->lst_cmdline->str, "<") == 0)
			input_redirection(&parse->lst_cmdline);
		if (ft_strcmp(parse->lst_cmdline->str, ">") == 0)
			output_redirection(&parse->lst_cmdline);
		//else if (ft_strcmp(parse->lst_cmdline->str, "<<") == 0)
		// 	ft_heredoc();
		if (ft_strcmp(parse->lst_cmdline->str, ">>") == 0)
			ft_append(&parse->lst_cmdline);
		if (parse->lst_cmdline->next == NULL)
			break;
		parse->lst_cmdline = parse->lst_cmdline->next;
	}
	while (parse->lst_cmdline->prev != NULL)
		parse->lst_cmdline = parse->lst_cmdline->prev;
}