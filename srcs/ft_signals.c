#include "../includes/minishell.h"

void	sig_quit(int param)
{
	(void)param;

	if (sig.child == 0 && sig.heredoc != 0)
	{
		dprintf(2, "AAA");
		write(1, "^\\Quit: 3\n", 10);
		sig.return_value = 131;
	}
	else if (sig.heredoc == 0)
	{
		rl_redisplay();
	}
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

	if (sig.heredoc == 0 && sig.child != 0)
	{
		sig.heredoc = 1;
		kill(sig.child_heredoc, SIGTERM);
	}
	else if (sig.child == 0 && sig.heredoc != 0)
	{
		write(2, "^C\n", 3);
		sig.return_value = 130;
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
