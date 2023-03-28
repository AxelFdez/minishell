#include "../../includes/minishell.h"

static int	ft_check_arg(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '-' && s[1] == 'n')
		i++;
	else
		return (1);
	while (s[i])
	{
		if (s[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}




void	ft_echo(t_list *tmp, t_parsing *parse)
{puts("ft_echo");
	int	nl;

	nl = 0;
	tmp = tmp->next;
	if (tmp != NULL && !ft_check_arg(tmp->str))
	{
		tmp = tmp->next;
		nl = 1;
	}
	while (tmp)
	{
		if (ft_strscmp(parse->meta, tmp->str) == 0)
			ft_putstr_fd(tmp->str, 1);
		tmp = tmp->next;
		if (tmp != NULL && ft_strscmp(parse->meta, tmp->str) == 0
			&& ft_strscmp(parse->meta, tmp->prev->str) == 0)
			write(1, " ", 1);
	}
	if (nl == 0)
		write(1, "\n", 1);
}
