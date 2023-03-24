#include "../../includes/minishell.h"

void	ft_cd(t_parsing *parse)
{
	t_list	*tmp;

	tmp = parse->lst_cmdline;
	// printf("%s\n", tmp->next->str);
	if (chdir(tmp->next->str) != 0)
	{
		perror("chdir");
		return ;
	}

}