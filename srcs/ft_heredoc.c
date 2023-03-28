#include "../includes/minishell.h"

void	one_pipe_heredoc(char **argv, char **env)
{
	t_cmd	cmd1;
	t_cmd	cmd2;
	pid_t	child;
	int		fd[2];
	int		pfd[2];

	pipe(pfd);
	child = fork();
	if (child == -1)
		error_exit("Fork error");
	else if (child == 0)
	{
		fd[0] = open("heredoc", O_RDONLY);
		cmd1 = parsing_cmd(argv[3], env);
		redirections(fd[0], pfd[1], pfd[0]);
		execve(cmd1.path, cmd1.cmd, env);
		error_exit("command not found");
	}
	fd[1] = open(argv[5], O_WRONLY | O_CREAT | O_APPEND, 0644);
	cmd2 = parsing_cmd(argv[4], env);
	redirections(pfd[0], fd[1], pfd[1]);
	close(fd[1]);
	wait(NULL);
	execve(cmd2.path, cmd2.cmd, env);
	error_exit("command not found");
}

int	first_pipe_heredoc(int temp_fd, char **argv, char **env)
{
	t_cmd	cmd1;
	pid_t	child;
	int		fd[1];
	int		pfd[2];

	pipe(pfd);
	child = fork();
	if (child == -1)
		error_exit("Fork error");
	else if (child == 0)
	{
		fd[0] = open("heredoc", O_RDONLY);
		cmd1 = parsing_cmd(argv[3], env);
		dup2(fd[0], STDIN_FILENO);
		dup2(pfd[1], STDOUT_FILENO);
		close(fd[0]);
		close(pfd[0]);
		execve(cmd1.path, cmd1.cmd, env);
		error_exit("command not found");
	}
	wait(NULL);
	temp_fd = pfd[0];
	close(pfd[1]);
	return (temp_fd);
}

void	last_pipe_heredoc(int argc, int temp_fd, char **argv, char **env)
{
	t_cmd	cmd1;
	t_cmd	cmd2;
	pid_t	child;
	int		pfd[2];
	int		fd[1];

	pipe(pfd);
	child = fork();
	if (child == -1)
		error_exit("Fork error");
	else if (child == 0)
	{
		cmd1 = parsing_cmd(argv[argc - 3], env);
		redirections(temp_fd, pfd[1], pfd[0]);
		execve(cmd1.path, cmd1.cmd, env);
		error_exit("command not found");
	}
	fd[0] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	cmd2 = parsing_cmd(argv[argc - 2], env);
	redirections(pfd[0], fd[0], pfd[1]);
	close(temp_fd);
	close(fd[0]);
	wait(NULL);
	execve(cmd2.path, cmd2.cmd, env);
	error_exit("command not found");
}

static void	get_input(char **argv)
{
	int		fd[1];
	int		i;
	char	*temp;

	temp = "";
	fd[0] = open("heredoc", O_WRONLY | O_CREAT | O_APPEND, 0644);
	while (ft_strncmp(temp, argv[2], ft_strlen(argv[2])) != 0)
	{
		i = 0;
		ft_printf("> ");
		temp = get_next_line(STDIN_FILENO);
		if (ft_strncmp(temp, argv[2], ft_strlen(argv[2])) == 0)
			break ;
		ft_putstr_fd(temp, fd[0]);
	}
	close(fd[0]);
}
void	ft_lst_strchr_pipe(t_parsing *parse)
{
	t_list *temp;
	temp = parse->lst_cmdline;

	while (temp)
	{
		if (ft_strchr(temp->str, '|') != NULL)
			return (0);
		temp = temp->next;
	}
	return (1);
}

void	*here_doc(int argc, char **argv, char **env)
{
	int		i;
	int		temp_fd;

	if (ft_lst_strchr_pipe(parse) == 1)
	{
		one_cmd_heredoc(parse);
	}
	get_input(argv);
	if (argc == 6)
		one_pipe_heredoc(argv, env);
	else
	{
		temp_fd = 0;
		temp_fd = first_pipe_heredoc(temp_fd, argv, env);
		i = 4;
		while (i < argc - 3)
		{
			temp_fd = middle_pipe(i, temp_fd, argv, env);
			i++;
		}
		last_pipe_heredoc(argc, temp_fd, argv, env);
	}
	return (0);
}