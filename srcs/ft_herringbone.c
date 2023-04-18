#include "../includes/minishell.h"

void	input_redirection(t_list **parse)
{
	int fd;
	ft_lstdel_current(&(*parse));
	if (access((*parse)->str, F_OK) != 0 || access((*parse)->str, R_OK) != 0)
	{
		perror((*parse)->str);
		sig.return_value = 1;
		while ((*parse) && ft_strcmp((*parse)->str, "|") != 0)
			ft_lstdel_current(&(*parse));
		return;
	}
	fd = open((*parse)->str, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	ft_lstdel_current(&(*parse));
}

void	output_redirection(t_list **parse)
{
	int fd;

	ft_lstdel_current(&(*parse));
	fd = open((*parse)->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror((*parse)->str);
		sig.return_value = 1;
		while ((*parse) && ft_strcmp((*parse)->str, "|") != 0)
			ft_lstdel_current(&(*parse));
		return;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_lstdel_current(&(*parse));
}

void	ft_append(t_list **parse)
{
	int fd;

	ft_lstdel_current(&(*parse));
	fd = open((*parse)->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror((*parse)->str);
		sig.return_value = 1;
		while ((*parse) && ft_strcmp((*parse)->str, "|") != 0)
			ft_lstdel_current(&(*parse));
		return;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_lstdel_current(&(*parse));
}

int check_herringbones_input(t_parsing *parse)
{
	t_list	*tmp;

	tmp = parse->lst_cmdline;
	while (tmp)
	{
		if (ft_strcmp(tmp->str, "<") == 0 || ft_strcmp(tmp->str, "<<") == 0
			|| ft_strcmp(tmp->str, ">") == 0 || ft_strcmp(tmp->str, ">>") == 0)
		{
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	check_herringbone(t_parsing *parse)
{
	parse->redirection_out = 0;
	while (check_herringbones_input(parse) == 0 && parse->lst_cmdline->str[0] != '|' && parse->lst_cmdline != NULL)
	{
		if (ft_strcmp(parse->lst_cmdline->str, "<") == 0)
		{
			parse->redirection_in = 1;
			input_redirection(&parse->lst_cmdline);
		}
		else if (ft_strcmp(parse->lst_cmdline->str, ">") == 0)
		{
			parse->redirection_out = 1;
			output_redirection(&parse->lst_cmdline);
		}
		else if (ft_strcmp(parse->lst_cmdline->str, ">>") == 0)
		{
			parse->redirection_out = 1;
			ft_append(&parse->lst_cmdline);
		}
		if (!parse->lst_cmdline || !parse->lst_cmdline->next || parse->lst_cmdline->str[0] == '|')
			break;
		if (parse->lst_cmdline->str[0] != '>' && parse->lst_cmdline->str[0] != '<')
			parse->lst_cmdline = parse->lst_cmdline->next;
	}
	if (parse->lst_cmdline)
		while (parse->lst_cmdline->prev != NULL)
			parse->lst_cmdline = parse->lst_cmdline->prev;
}