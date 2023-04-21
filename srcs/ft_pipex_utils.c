/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axfernan <axfernan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:06:54 by axfernan          #+#    #+#             */
/*   Updated: 2023/04/20 22:21:36 by axfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**find_path_in_env(t_parsing *parse)
{
	int		i;
	char	*path;
	char	**split;

	i = 0;
	path = NULL;
	while (parse->env[i])
	{
		if (ft_strncmp(parse->env[i], "PATH", 4) == 0)
			path = (parse->env[i] + 5);
		i++;
	}
	if (!path)
		return (NULL);
	split = ft_split(path, ':');
	i = 0;
	while (split[i])
	{
		split[i] = ft_strjoin_free_s1(split[i], "/");
		split[i] = ft_strjoin_free_s1(split[i], parse->command[0]);
		i++;
	}
	return (split);
}

static char	*env_path_command(t_parsing *parse)
{
	int		i;
	int		j;
	char	**split;

	split = find_path_in_env(parse);
	if (!split || !split[0])
		return (NULL);
	i = 0;
	while (access(split[i], F_OK) != 0)
	{
		i++;
		if (split[i] == 0)
		{
			j = 0;
			while (j < i)
			{
				free(split[j]);
				j++;
			}
			free(split);
			return (parse->command[0]);
		}
	}
	return (split[i]);
}

static void	cmd_lst_to_tab(t_parsing *parse)
{
	int		i;
	t_list	*temp;

	temp = parse->lst_cmdline;
	i = 0;
	while (temp && ft_strcmp(temp->str, "|") != 0)
	{
		i++;
		temp = temp->next;
	}
	parse->command = NULL;
	parse->command = malloc(sizeof(char *) * (i + 1));
	if (!parse->command)
		perror("error malloc");
	i = 0;
	parse->lst_target = 0;
	temp = parse->lst_cmdline;
	while (temp && ft_strcmp(temp->str, "|") != 0)
	{
		parse->command[i] = ft_strdup(temp->str);
		i++;
		parse->lst_target++;
		temp = temp->next;
	}
	parse->command[i] = 0;
}

void	parsing_cmd(t_parsing *parse)
{
	cmd_lst_to_tab(parse);
	if (access(parse->command[0], F_OK) && access(parse->command[0], X_OK))
		parse->command[0] = env_path_command(parse);
	if (!parse->command[0])
		ft_printf("minishell: %s: no such file or directory\n",
			parse->lst_cmdline->str);
}

int	count_pipe(t_list *list)
{
	t_list	*temp;
	int		count;

	count = 0;
	temp = list;
	while (temp)
	{
		if (temp->str[0] == '|')
			count++;
		temp = temp->next;
	}
	return (count);
}
