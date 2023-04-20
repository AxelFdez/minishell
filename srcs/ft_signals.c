/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axfernan <axfernan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:09:58 by axfernan          #+#    #+#             */
/*   Updated: 2023/04/20 11:31:42 by axfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_quit(int param)
{
	(void)param;
	if (g_sig.child == 0)
	{
		write(1, "^\\Quit: 3\n", 10);
		g_sig.return_value = 131;
		return ;
	}
	if (g_sig.heredoc == 0)
		rl_redisplay();
	else
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_int(int param)
{
	(void)param;
	if (g_sig.child == 0)
	{
		write(2, "^C\n", 3);
		g_sig.return_value = 130;
		return ;
	}
	if (g_sig.heredoc == 0)
	{
		write(2, "\n", 1);
		g_sig.return_value = 1;
		kill(g_sig.child_heredoc, SIGTERM);
	}
	else
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig.return_value = 1;
	}
}

void	signals_func(void)
{
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_int);
}
