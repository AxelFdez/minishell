#include "../../includes/minishell.h"

static int	ft_strscmp(t_parsing *parse, char *s)
{
	int	i;

	i = 0;
	while (parse->meta[i])
	{
		if (ft_strcmp(s, parse->meta[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_echo(t_parsing *parse)
{
	while (parse->lst_cmdline)
	{
		if (ft_strcmp(parse->lst_cmdline->str, "echo") == 0)
		{
			parse->lst_cmdline = parse->lst_cmdline->next;
			while (parse->lst_cmdline)
			{
				if (ft_strscmp(parse, parse->lst_cmdline->str) == 0)
				{
					ft_putstr_fd(parse->lst_cmdline->str, 1);
					write(1, " ", 1);
				}
				parse->lst_cmdline = parse->lst_cmdline->next;
			}
		}
		if (parse->lst_cmdline == NULL)
			break ;
		parse->lst_cmdline = parse->lst_cmdline->next;
	}
}
