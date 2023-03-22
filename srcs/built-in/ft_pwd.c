#include "../../includes/minishell.h"

void	ft_pwd(t_parsing *parse)
{
	t_list	*tmp;

	if (!parse->lst_env)
	{
		ft_putstr_fd("Error print pwd\n", 2);
		return ;
	}
	tmp = parse->lst_env;
	while (tmp)
	{
		if (ft_strnstr(tmp->str, "PWD=", ft_strlen(tmp->str)))
		{
			ft_printf("%s\n", ft_strchr(tmp->str, '/'));
			break ;
		}
		tmp = tmp->next;
	}
}