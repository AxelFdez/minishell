

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../linked_list/lst.h"



typedef struct s_parsing
{
	char			*input;
	char			*prompt;
	char			*tmp;
	char			*cmd;
	char			*path_cmd;
	t_list			*lst_cmdline;
	int		i;
	int		len;
}				t_parsing;


void	ft_parsing(char *input);
void	ft_get_cmdline(t_parsing *parse);
void	ft_quotes(t_parsing *parse);
void	ft_fill_lst(t_list **lst, t_parsing *parse, int start, int len);
void	ft_error(char *err_mess);
int		is_close_herringbone(t_parsing *parse);
int		is_open_herringbone(t_parsing *parse);
int		is_pipe(t_parsing *parse);






#endif