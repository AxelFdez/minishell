
#include "../includes/minishell.h"

int ft_lst_strchr_meta(t_list *list)
{
	t_list *temp;
	temp = list;

	while (temp)
	{
		if (ft_strchr(temp->str, '|') != NULL)
			return (0);
		else if (ft_strchr(temp->str, '>') != NULL)
			return (0);
		else if (ft_strchr(temp->str, '<') != NULL)
			return (0);
		temp = temp->next;
	}
	return (1);
}

void execute_cmd(t_parsing *parse)
{
	// 1- watch on redirection
	// 2 execute cmd
	// 3 where ?
	pid_t child;
	child = fork();
	if (child < 0)
		perror("fork error\n");
	else if (child == 0)
	{
		parsing_cmd(parse);
		if (ft_lst_strchr_meta(parse->lst_cmdline) == 0)
			pipex(parse);
	// 	int i = 0;
	// while (parse->command[i])
	// {
	// 	printf("cmd[%d] = %s\n", i, parse->command[i]);
	// 	i++;
	// }
	// ft_lstprint_from_head(parse->lst_cmdline);
	//  exit(EXIT_FAILURE);
		execve(parse->command[0], parse->command, parse->env);
		perror("command not found");
	}
	wait(NULL);
		// int i = 0;
		// while (parse->command[i])
		// {
		// 	free(parse->command[i]);
		// 	i++;
		// }
		// free(parse->command);
	//to_free(parse->command, 0);
	return ;
}

