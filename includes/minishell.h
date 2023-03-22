

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_parsing
{
	int		i;
	int		j;
	int		k;
	char	c;
	char	*meta[6];
	int		len;
	int		quote_to_del;
	char	*input;
	char	*prompt;
	t_list	*lst_cmdline;
	t_list	*lst_env;
}				t_parsing;

void	ft_parsing(char *input);
void	ft_get_cmdline(t_parsing *parse);
void	ft_quotes(t_parsing *parse);
void	ft_fill_lst(t_list **lst, t_parsing *parse, int start);
void	ft_error(char *err_mess);
int		is_close_herringbone(t_parsing *parse);
int		is_open_herringbone(t_parsing *parse);
int		is_pipe(t_parsing *parse);
int		ft_check_syntax(t_parsing *parse);
void	ft_initialization(t_parsing *parse);
void	ft_strdel_quotes(t_parsing *parse, char *str);
int		is_meta_char(int c);
void	ft_check_built_in(t_parsing *parse);


void	ft_echo(t_list *tmp, t_parsing *parse, int nl);
void	ft_env(t_parsing *parse);
void	ft_pwd(t_parsing *parse);
void	ft_export(t_parsing *parse);
#endif