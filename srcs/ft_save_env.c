#include "../includes/minishell.h"


void	ft_save_env(t_parsing *parse)
{
	t_list	*tmp;

	parse->fd_env = open("env.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (parse->fd_env < 0)
		perror("env.txt");
	tmp = parse->lst_env;
	while (tmp)
	{
		ft_putstr_fd(tmp->str, parse->fd_env);
		write (parse->fd_env, "\n", 1);
		tmp = tmp->next;
	}
	tmp = parse->lst_env;
	close(parse->fd_env);
}