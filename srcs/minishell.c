#include "../includes/minishell.h"

// char	**separate_cmd_to_flags(char *cmd)
// {
// 	char	**flags;

// 	flags = ft_split(cmd, ' ');
// 	return (flags);
// }

// t_cmd	parsing_cmd(char *argv, char **env)
// {
// 	t_cmd	cmd;

// 	cmd.cmd = separate_cmd_to_flags(argv);
// 	cmd.path = path_of_command(env, cmd.cmd[0]);
// 	if (cmd.path[0] == '\0')
// 	{
// 		to_free(cmd.cmd, cmd.path);
// 		exit(EXIT_FAILURE);
// 	}
// 	cmd.cmd[0] = cmd.path;
// 	return (cmd);
// }

// static char	**find_path_in_env(char **env, char *cmd)
// {
// 	int		i;
// 	char	*path;
// 	char	**split;

// 	i = 0;
// 	while (ft_strstr(env[i], "PATH") == NULL)
// 		i++;
// 	path = env[i];
// 	path = ft_strtrim(path, "PATH=");
// 	split = ft_split(path, ':');
// 	free(path);
// 	i = 0;
// 	while (split[i])
// 	{
// 		split[i] = ft_strjoin_free(split[i], "/");
// 		split[i] = ft_strjoin_free(split[i], cmd);
// 		i++;
// 	}
// 	return (split);
// }

// char	*path_of_command(char **env, char *cmd)
// {
// 	int		i;
// 	int		j;
// 	char	**split;

// 	split = find_path_in_env(env, cmd);
// 	i = 0;
// 	while (access(split[i], F_OK) != 0)
// 	{
// 		i++;
// 		if (split[i] == 0)
// 		{
// 			perror("command not found");
// 			j = 0;
// 			while (j < i)
// 			{
// 				free(split[j]);
// 				j++;
// 			}
// 			free(split);
// 			return (NULL);
// 		}
// 	}
// 	return (split[i]);
// }

// void excecute_cmd (t_parsing parse)
// {
// 	pid_t	child;

// 	child = fork();
// 	if (child < 0)
// 		perror("fork error");
// 	else if (fork == 0)
// 	{
// 		parse.cmd = check_command(parse.lst_cmdline);
// 	}
// }

// void simple_exec(t_parsing parse, char **env)
// {
// 	pid_t	child;
// 	char	*cmd;
// 	int		fd[2];

// 	child = fork();
// 	if (child == -1)
// 	{
// 		perror("fork error");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (child == 0)
// 	{
// 		fd[0] = open(argv[0], O_RDONLY);
// 		fd[1] = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		dup2(fd_in, STDIN_FILENO);
// 		dup2(fd_out, STDOUT_FILENO);
// 		close(fd_in);
// 		close(fd_close);
// 		execve(parse.path_cmd, parse.cmd, env);
// 		perror("command not found");
// 	}
// 	wait(NULL);
// }

int main(int argc, char **argv, char **env)
{
    // char *input;
	(void)argc;
	(void)argv;
	(void)env;
    t_parsing   parse;
    // int   db_coat = 0;

    // Boucle de lecture d'entrée utilisateur
    while (1) {
        // Utilise readline pour lire l'entrée utilisateur
        parse.input = readline("minishell$ ");
		// parsing ici
	    // printf("%s\n", input);
        add_history(parse.input);
        if (!parse.input || !strcmp(parse.input, "")) {
            break;
        }

        ft_get_cmdline(&parse);
		//execute_cmd(&parse, env);
        // Si l'utilisateur entre une chaîne vide, quitte la boucle
        // Affiche l'entrée utilisateur et l'ajoute à l'historique
        // printf("Vous avez entré : %s\n", input);
		//ajoute la ligne en historique
        // Libère la mémoire allouée pour l'entrée utilisateur
        // free(parse.input);
    }

    // puts("end");
    // system("leaks minishell");
    return 0;
}