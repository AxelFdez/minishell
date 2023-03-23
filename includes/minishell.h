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
# include <signal.h>

typedef struct s_cmd
{
	char	*path;
	char	**cmd;
}	t_cmd;

typedef struct s_parsing
{
	int		i;
	int		j;
	int		k;
	char	c;
	int		len;
	int		quote_to_del;
	char	*input;
	char	*prompt;
	char	**env;
	t_list	*lst_cmdline;
	t_list	*lst_env;
	char	**command;
	int		lst_target;
}				t_parsing;


void	rl_replace_line(const char *text, int clear_undo);

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
void	handle_signals(int sig);
void	ft_strdel_quotes(t_parsing *parse, char *str);
void	signals_(void);
char	*path_of_command(t_parsing *parse);
void	cmd_lst_to_tab(t_parsing *parse);
void	parsing_cmd(t_parsing *parse);
void execute_cmd(t_parsing *parse);

#endif
