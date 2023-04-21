/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axfernan <axfernan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:31:01 by axfernan          #+#    #+#             */
/*   Updated: 2023/04/20 11:31:02 by axfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_error_identifier(char *s)
{
	ft_printf("export: `%s': not a valid identifier\n", s);
	g_sig.return_value = 1;
}

void	ft_unset(t_parsing *parse)
{
	t_list	*tmp_cmd;
	t_list	*tmp_env;

	tmp_cmd = parse->lst_cmdline->next;
	tmp_env = parse->lst_env;
	if (tmp_cmd == NULL)
		return ;
	while (tmp_cmd)
	{
		if (ft_strlen(tmp_cmd->str) == 0)
			ft_error_identifier(tmp_cmd->str);
		tmp_env = parse->lst_env;
		while (tmp_env)
		{
			if (!ft_strncmp(tmp_cmd->str, tmp_env->str,
					ft_str_chr(tmp_env->str, '='))
						&& (!ft_strnstr(tmp_env->str, tmp_cmd->str, 2)))
			{
				ft_lstdel_actual(&parse->lst_env, tmp_env);
				break ;
			}
			tmp_env = tmp_env->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
}
