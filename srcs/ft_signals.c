#include "../includes/minishell.h"

void	sig_quit(int param)
{
	(void)param;
	if (sig.child == 0)
	{
		write(1, "^\\Quit: 3\n", 10);
		sig.return_value = 131;
		return;
	}
	if (sig.heredoc == 0)
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
	if (sig.child == 0)
	{
		write(2, "^C\n", 3);
		sig.return_value = 130;
		return;
	}
	if (sig.heredoc == 0)
	{
		write(2, "\n", 1);
		sig.return_value = 1;
		kill(sig.child_heredoc, SIGTERM);
	}
	else
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		sig.return_value = 1;
	}
}

void	signals_func(void)
{
		signal(SIGQUIT, sig_quit);
		signal(SIGINT, sig_int);
}
