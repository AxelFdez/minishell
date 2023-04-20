#include "../../includes/minishell.h"

static int	ft_str_isdigits(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		i++;
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 1)
			i++;
		else
			return (0);
	}
	return (1);
}

static void	ft_handle_error(t_parsing *parse)
{
	ft_printf("minishell: exit: %s: numeric argument required\n",
		parse->lst_cmdline->next->str);
	parse->ret_value = 255;
	exit(255);
}

void	ft_exit(t_parsing *parse)
{
	unsigned long long	ret_atoi;
	if (parse->lst_cmdline->next == NULL)
	{
		if (g_sig.child != 0)
			write(1, "exit\n", 5);
		exit (0);
	}
	else
	{
		if (ft_str_isdigits(parse->lst_cmdline->next->str) == 1
			&& ft_lstsize(parse->lst_cmdline) > 2)
			ft_printf("minishell: exit: too many arguments\n");
		else if (ft_str_isdigits(parse->lst_cmdline->next->str) == 0)
			ft_handle_error(parse);
		else
		{
			ret_atoi = ft_atoi_llu(parse->lst_cmdline->next->str);
			if ((parse->lst_cmdline->next->str[0] != '-'
					&& ret_atoi <= 1844674407370955169)
				|| (parse->lst_cmdline->next->str[0] == '-'
					&& ret_atoi >= 1844674407370955169))
				parse->ret_value = ret_atoi % 256;
			write(2, "exit\n", 5);
			exit(ret_atoi % 256);
		}
	}
}
