#include "../../includes/minishell.h"


void	ft_unset(t_parsing *parse)
{
    t_list  *tmp_cmd;
    t_list  *tmp_env;
    // t_list  *tmp;
    
    tmp_cmd = parse->lst_cmdline->next;
    tmp_env = parse->lst_env;

    if (tmp_cmd == NULL)
        return ;
    while (tmp_cmd)
    {
        tmp_env = parse->lst_env;
        while (tmp_env)
        {
            if (ft_strnstr(tmp_env->str, tmp_cmd->str, ft_strlen(tmp_cmd->str)))
            {
                // printf("value = %s\n", tmp_env->str);
                ft_lstdel_actual(tmp_env);
                // if (tmp_env->next == NULL)
                // {
                //     puts("equal NULL");
                //     tmp_env->prev->next = NULL;
                //     free(tmp_env);
                // }
                // else if (tmp_env->prev == NULL)
                // {
                //     // tmp_env->next->prev = NULL;
                //     // free(tmp_env);
                // }
                // else
                // {puts("AAA");
                //     tmp = tmp_env;
                //     tmp_env = tmp_env->prev;
                //     tmp_env->next = tmp_env->next->next;
                //     tmp_env->next->prev = tmp_env;
                //     free(tmp);

                //   printf("tmp = %s\n", tmp_env->str);

                   
                // }
            }
            tmp_env = tmp_env->next;
        }
        tmp_cmd = tmp_cmd->next;
    }
}
