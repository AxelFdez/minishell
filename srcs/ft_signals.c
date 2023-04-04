#include "../includes/minishell.h"

// int get_pid(void)
// {
// 	pid_t child;
// 	char *tab[3];
// 	char *env[1];
// 	tab[0] = "/bin/echo";
// 	tab[1] = NULL;
// 	//tab[2] = NULL;
// 	env[0] = NULL;
// 	child = fork();
// 	if (child < 0)
// 		perror("fork error");
// 	else if (child == 0)
// 	{
// 		int fd[2];
// 		fd[0] = open("test.txt", O_RDONLY);
// 		fd[1] = open("out.txt", O_WRONLY);
// 		dup2(fd[0], STDIN_FILENO);
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		execve("/bin/echo", tab, env);
// 		perror("error exec");
// 	}
// 	int fd[1];
// 	wait(NULL);
// 	fd[0] = open("out.txt", O_RDONLY);
// 	printf("pid = %s\n", get_next_line(fd[0]));
// 	close(fd[0]);
// 	return 0;
// }

void handle_signals(int sig)
{
	//int pid = getpid();
	if (sig == 2)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == 3)
	{
		signal(SIGSTOP, SIG_IGN);
		//kill(pid, SIGCONT);
	}
	if (sig == 15)
	{

		write(1, "exit\n", 5);
		//kill (pid, SIGTERM);
	}
}

void signals_(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_signals;
	sa.sa_flags = SA_RESTART;
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGSTOP);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGSTOP, &sa, NULL);
}