#include "../../includes/minishell.h"


int	ft_env(t_parsing *parse)
{
	t_list	*tmp;
	int		error;

	tmp = parse->lst_env;
	error = 0;
	if (parse->lst_cmdline->next == NULL
		|| ft_strcmp(parse->lst_cmdline->next->str, "|") == 0)
	{
		while (tmp)
		{
			if (ft_strnstr(tmp->str, "=", ft_strlen(tmp->str)))
				ft_printf("%s\n", tmp->str);
			tmp = tmp->next;
		}
	}
	else
	{
		ft_printf("env: `%s' : not a valid identifier\n",
			parse->lst_cmdline->next->str);
		error++;
	}
	if (error > 0)
		return (1);
	return (0);
}
