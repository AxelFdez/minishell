#include "../includes/minishell.h"

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


void ft_heredoc(t_parsing *parse, t_list **lst)
{
	char *temp;
	int pfd[2];
	t_list *temp_list;

	temp_list = (*lst);
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
	while ((*lst) && (*lst)->next && ft_strcmp((*lst)->str, "|") != 0)
	{
		if (ft_strcmp((*lst)->str, "<<") == 0)
		{
			ft_lstdel_current(&(*lst));
			tab[i] = ft_strdup((*lst)->str);
			i++;
			ft_lstdel_current(&(*lst));
		}
		else
			(*lst) = (*lst)->next;
	}
	tab[i] = 0;
	temp = "";
	pipe(pfd);
	int j = 0;
	while (1)
	{
		//puts("AAA");
		if (sig.int_heredoc == 1)
			{
				//puts("BBB");
				sig.return_value = 1;
				ft_lstdel_all(&parse->lst_cmdline);
				break;
			}
		sig.heredoc = 1;
		temp = readline("> ");
		if (!temp || sig.int_heredoc == 1)
			break ;
		if (i == 1)
		{
			if (ft_strcmp(temp, tab[j]) == 0)
				break;
			temp = ft_handle_dollar_in_heredoc(parse, temp);
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
	sig.heredoc = 0;
	sig.int_heredoc = 0;
	close(pfd[1]);
	parse->heredoc_pfd = pfd[0];
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	if (!parse->lst_cmdline)
	{
		close(pfd[0]);
		return ;
	}
	else
		while ((*lst)->prev != NULL)
			(*lst) = (*lst)->prev;
}