#include "../../includes/minishell.h"


void	ft_export(t_parsing *parse)
{
    size_t     i;
    t_list  *new;
    t_list  *tmp;
    
    i = 0;
    tmp = parse->lst_cmdline->next;
    if (tmp == NULL)
    {
        ft_print_sorted_env(parse);
        return ;
    }
    while (tmp)
    {
        while (ft_isalnum(tmp->str[i]) || tmp->str[i] == '_'
            || tmp->str[i] == '=')
            i++;
        if (i == ft_strlen(tmp->str))
        {
            new = ft_lstnew(tmp->str);
            ft_lstadd_back(&parse->lst_env, new);
        }
        else
            ft_printf("export: `%s' : not a valid identifier\n", tmp->str);
        i = 0;
        tmp = tmp->next;
    }
}
