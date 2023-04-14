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

static void	ft_print_var(t_parsing *parse, char *s)
{
	int		i;
	char	*str;

	if (parse->is_in_str == 1)
	{
		ft_putstr(s);
		return ;
	}
	i = 0;
	str = ft_strtrim(s, " ");
	while (str[i])
	{
		write (1, &str[i], 1);
		if (str[i] == ' ')
			while (str[i] == ' ')
				i++;
		else
			i++;
	}
	free(str);
}

static void	ft_print_tild(t_parsing *parse)
{
	char	*tild_ret;

	tild_ret = ft_loop_tild_hyphen(parse, '~');
	ft_putstr_fd(tild_ret, 1);
	
	free(tild_ret);
}

void	ft_echo(t_list *tmp, t_parsing *parse)
{
	int	nl;

	nl = 0;
	tmp = tmp->next;
	if (tmp != NULL && !ft_check_arg(tmp->str))
	{
		tmp = tmp->next;
		nl = 1;
	}
	while (tmp && ft_strcmp(tmp->str, "|") != 0)
	{
		if (ft_strcmp(tmp->str, "~") == 0)
			ft_print_tild(parse);
		else
			ft_print_var(parse, tmp->str);
		tmp = tmp->next;
		if (tmp != NULL && ft_strscmp(parse->meta, tmp->str) == 0
			&& ft_strscmp(parse->meta, tmp->prev->str) == 0)
			write(1, " ", 1);
	}
	if (nl == 0)
		write(1, "\n", 1);
}
