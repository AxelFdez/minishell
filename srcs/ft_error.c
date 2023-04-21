/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axfernan <axfernan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:31:05 by axfernan          #+#    #+#             */
/*   Updated: 2023/04/21 12:09:08 by axfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_error(char *err_mess)
{
	write (2, "Error\n", 6);
	ft_putstr_fd(err_mess, 2);
	g_sig.return_value = 1;
}

static void	directory_error(t_parsing *parse)
{
	if (access(parse->command[0], F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(parse->command[0], 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		g_sig.return_value = 127;
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(parse->command[0], 2);
		if (!access(parse->command[0], R_OK))
			ft_putstr_fd(": is a directory\n", 2);
		else
			ft_putstr_fd(": Permission denied\n", 2);
		g_sig.return_value = 126;
	}
}

void	error_exec_message(t_parsing *parse)
{
	if (!parse->command[0])
		return ;
	if (parse->command[0][0] == '/'
		|| (parse->command[0][0] == '.' && parse->command[0][1] == '/'))
	{
		directory_error(parse);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(parse->command[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		g_sig.return_value = 127;
	}
}
