#include "../includes/minishell.h"

void	ft_lstdel_current(t_list **lst)
{
	t_list *temp;

	temp = (*lst);
	if (!(*lst))
		return ;
	if ((*lst)->prev == NULL)
	{
		ft_lstdel_front(&(*lst));
	}
	else if ((*lst)->next == NULL)
	{
		(*lst) = (*lst)->prev;
		ft_lstdel_back(&(*lst));
	}
	else
	{
		temp = (*lst)->next;
		((*lst)->prev)->next = (*lst)->next;
		((*lst)->next)->prev = (*lst)->prev;
		free((*lst)->str);
		free((*lst));
		(*lst) = temp;
	}
}

void	input_redirection(t_list **parse)
{
	int fd;
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
		perror((*parse)->str);
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
		perror((*parse)->str);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_lstdel_current(&(*parse));
}

void ft_heredoc(t_list **parse)
{
	char *temp;
	int pfd[2];
	t_list *temp_list;

	temp_list = (*parse);
	int i = 0;
	while (temp_list && ft_strcmp(temp_list->str, "|") != 0)
	{
		if (ft_strcmp(temp_list->str, "<<") == 0)
			i++;
		temp_list = temp_list->next;
	}
	char **tab;

	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		perror("malloc error");

	i = 0;
	while ((*parse) && (*parse)->next && ft_strcmp((*parse)->str, "|") != 0)
	{
		if (ft_strcmp((*parse)->str, "<<") == 0)
		{
			ft_lstdel_current(&(*parse));
			tab[i] = ft_strdup((*parse)->str);
			i++;
			ft_lstdel_current(&(*parse));
		}
		else
			(*parse) = (*parse)->next;
	}
	tab[i] = 0;
	temp = "";
	pipe(pfd);
	int j = 0;
	while (1)
	{
		signals_(1);
		temp = readline("> ");
		if (i == 1)
		{
			if (ft_strcmp(temp, tab[j]) == 0)
				break;
			ft_putstr_fd(temp, pfd[1]);
			ft_putstr_fd("\n", pfd[1]);
		}
		if (i > 1)
		{
			if (ft_strcmp(temp, tab[j]) == 0)
			{
				j++;
				i--;
			}
		}
	}
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	while ((*parse)->prev != NULL)
		(*parse) = (*parse)->prev;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}


// void ft_heredoc(t_list **parse)
// {
// 	char *temp;
// 	int pfd[2];

// 	temp = "";
// 	pipe(pfd);

// 	ft_lstdel_current(&(*parse));
// 	while (1)
// 	{
// 		signals_(1);
// 		temp = readline("> ");
// 		//print_list((*parse));
// 		if (ft_strcmp(temp, (*parse)->str) == 0)
// 			break ;
// 		ft_putstr_fd(temp, pfd[1]);
// 		ft_putstr_fd("\n", pfd[1]);
// 	}
// 	close(pfd[1]);
// 	dup2(pfd[0], STDIN_FILENO);
// 	close(pfd[0]);
// 	ft_lstdel_current(&(*parse));
// }

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

int ft_lst_strchr_heredoc(t_list *list)
{
	t_list *temp;
	temp = list;

	while (temp)
	{
		if (ft_strcmp(temp->str, "<<") == 0)
			return (0);
		temp = temp->next;
	}
	return (1);
}

void	check_herringbone(t_parsing *parse)
{
	parse->redirection_out = 0;
	parse->fd_stdout = dup(STDOUT_FILENO);
	while (check_herringbones_input(parse) == 0 && parse->lst_cmdline->str[0] != '|' && parse->lst_cmdline != NULL)
	{
		if (ft_strcmp(parse->lst_cmdline->str, "<") == 0)
			input_redirection(&parse->lst_cmdline);
		else if (ft_strcmp(parse->lst_cmdline->str, ">") == 0)
		{
			parse->redirection_out = 1;
			output_redirection(&parse->lst_cmdline);
		}
		else if (ft_strcmp(parse->lst_cmdline->str, "<<") == 0)
		{
				ft_heredoc(&parse->lst_cmdline);
		}
		else if (ft_strcmp(parse->lst_cmdline->str, ">>") == 0)
			ft_append(&parse->lst_cmdline);
		if (!parse->lst_cmdline || !parse->lst_cmdline->next || parse->lst_cmdline->str[0] == '|')
			break;
		if (parse->lst_cmdline->str[0] != '>' && parse->lst_cmdline->str[0] != '<')
			parse->lst_cmdline = parse->lst_cmdline->next;
	}
	while (parse->lst_cmdline->prev != NULL)
		parse->lst_cmdline = parse->lst_cmdline->prev;
	if (!parse->lst_cmdline)
			exit(EXIT_SUCCESS);
}