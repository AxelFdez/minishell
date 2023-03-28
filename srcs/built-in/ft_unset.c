#include "../../includes/minishell.h"

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
		tmp_env = parse->lst_env;
		while (tmp_env)
		{
			if (!ft_strncmp(tmp_cmd->str, tmp_env->str,
					ft_str_chr(tmp_env->str, '=')))
				ft_lstdel_actual(&parse->lst_env, tmp_env);
			tmp_env = tmp_env->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
}
