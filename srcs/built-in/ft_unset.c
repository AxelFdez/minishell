/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmassa <chmassa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:31:01 by axfernan          #+#    #+#             */
/*   Updated: 2023/04/21 10:51:49 by chmassa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

static void	ft_error_identifier(char *s)
{
	ft_printf("export: `%s': not a valid identifier\n", s);
	g_sig.return_value = 1;
}

static void	ft_env_loop(t_parsing *parse, char *s1)
{
	char	*s2;
	t_list	*tmp_env;

	tmp_env = parse->lst_env;
	while (tmp_env)
	{
		s2 = ft_set_str_to_comp(tmp_env->str);
		if (ft_strcmp(s1, s2) == 0)
		{
			ft_lstdel_actual(&parse->lst_env, tmp_env);
			free(s2);
			return ;
		}
		tmp_env = tmp_env->next;
		free(s2);
	}
}

void	ft_unset(t_parsing *parse)
{
	t_list	*tmp_cmd;
	char	*s1;

	tmp_cmd = parse->lst_cmdline->next;
	if (tmp_cmd == NULL)
		return ;
	if (ft_strcmp(tmp_cmd->str, "_") == 0)
		return ;
	while (tmp_cmd)
	{
		s1 = ft_set_str_to_comp(tmp_cmd->str);
		if (ft_strlen(tmp_cmd->str) == 0)
			ft_error_identifier(tmp_cmd->str);
		ft_env_loop(parse, s1);
		free(s1);
		tmp_cmd = tmp_cmd->next;
	}
}
