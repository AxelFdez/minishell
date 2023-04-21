/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axfernan <axfernan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:11:48 by axfernan          #+#    #+#             */
/*   Updated: 2023/04/21 12:26:27 by axfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	exit_without_arg(void)
{
	write(2, "exit\n", 5);
	exit (0);
}

void	ft_exit(t_parsing *parse)
{
	unsigned long long	ret_atoi;

	if (parse->lst_cmdline->next == NULL)
		exit_without_arg();
	else
	{
		if (ft_str_isdigits(parse->lst_cmdline->next->str) == 1
			&& ft_lstsize(parse->lst_cmdline) > 2)
			ft_printf("minishell: exit: too many arguments\n");
		else if (ft_str_isdigits(parse->lst_cmdline->next->str) == 0
			|| ft_strlen(parse->lst_cmdline->next->str) > 19)
			ft_handle_error(parse);
		else
		{
			ret_atoi = ft_atoi_llu(parse->lst_cmdline->next->str);
			if ((parse->lst_cmdline->next->str[0] != '-'
					&& ret_atoi <= 1844674407370955169)
				|| (parse->lst_cmdline->next->str[0] == '-'
					&& ret_atoi >= 1844674407370955169))
				g_sig.return_value = ret_atoi % 256;
			write(2, "exit\n", 5);
			exit(ret_atoi % 256);
		}
	}
}
