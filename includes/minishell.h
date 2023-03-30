#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <signal.h>

typedef struct s_cmd
{
	char	*path;
	char	**cmd;
}	t_cmd;

int value_return;

typedef struct s_parsing
{
	int		ret_value;
	int		tmp_ret_value;
	int		i;
	int		j;
	int		k;
	int		dollar;
	char	*str_tmp;
	char	var_name[1024];
	char	c;
	char	*meta[6];
	int		len;
	int		quote_to_del;
	char	*input;
	char	*prompt;
	char	**env;
	t_list	*lst_cmdline;
	t_list	*lst_env;
	char	**command;
	int		lst_target;
	int		fd[2];
	int		built_in_cmd;
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
void	execute_cmd(t_parsing *parse);
char	*path_of_command(t_parsing *parse);
int		count_pipe_until_sep(t_list *list);
void	one_pipe(t_parsing *parse);
int		first_pipe(t_parsing *parse, int temp_fd);
int		middle_pipe(t_parsing *parse, int pipe_temp);
void	last_pipe(t_parsing *parse, int temp_fd);
void	pipex(t_parsing *parse);
int		ft_lst_strchr_meta(t_list *list);
void	cmd_lst_to_tab(t_parsing *parse);
int		is_meta_char(int c);
void	ft_check_built_in(t_parsing *parse);
void	ft_sort_env(t_list **lst);
void	ft_echo(t_list *tmp, t_parsing *parse);
int		ft_env(t_parsing *parse);
int		ft_pwd(void);
int		ft_export(t_parsing *parse);
void	ft_print_sorted_env(t_parsing *parse);
void	ft_handle_dollar_no_quotes(t_parsing *parse);
void	ft_handle_dollar_in_str(t_parsing *parse);
int		check_builtin_input(t_parsing * parse);
void	execute_built_in(t_parsing *parse);
int		parsing_built_in(t_parsing *parse);
void	check_herringbone(t_parsing *parse);
void	input_redirection(t_list **parse);
void	output_redirection(t_list **parse);
void	ft_append(t_list **parse);
void	check_herringbone(t_parsing *parse);
void	ft_unset(t_parsing *parse);
void	ft_exit(t_parsing *parse);
void	ft_print_export(t_parsing *parse);
void	ft_handle_dollar(t_parsing *parse);
int		ft_cd(t_parsing *parse);
int		ft_lst_strchr_pipe(t_list *list);
void	cd_in_cmdline(t_parsing *parse);

#endif
