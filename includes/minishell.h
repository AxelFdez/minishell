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
# include <sys/wait.h>
# include <errno.h>
# include <termios.h>

typedef struct s_cmd
{
	char	*path;
	char	**cmd;
}	t_cmd;

int sig_child;

typedef struct s_parsing
{
	int		is_in_str;
	int		ret_value;
	int		tmp_ret_value;
	int		i;
	int		i_b;
	int		j;
	int		k;
	int		fd_history[2];
	int		is_dollar;
	char	*str_tmp;
	char	var_name[1024];
	char	c;
	char	*meta[6];
	char	*s1;
	char	*s2;
	char	*tmp_input;
	int		len;
	int		len_b;
	int		quote_to_del;
	char	*input;
	char	*prompt;
	char	**env;
	t_list	*lst_cmdline;
	t_list	*lst_env;
	char	**command;
	int		lst_target;
	int		built_in_cmd;
	int		redirection_out;
	int		redirection_in;
	struct termios term;
	int		temp_fd;
	int		status;
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
void	signals_(int heredoc);
void	parsing_cmd(t_parsing *parse);
void	execute_cmd(t_parsing *parse);
int		count_pipe(t_list *list);
void	one_pipe(t_parsing *parse);
void	pipex(t_parsing *parse);
int		ft_lst_strchr_meta(t_list *list);
int		is_meta_char(int c);
void	ft_check_built_in(t_parsing *parse);
//**** built-in *********************************************************************
void	ft_sort_env(t_list **lst);
void	ft_echo(t_list *tmp, t_parsing *parse);
int		ft_pwd(void);
int		ft_export(t_parsing *parse);
int		ft_env(t_parsing *parse);
void	ft_print_sorted_env(t_parsing *parse);
void	ft_handle_dollar_no_quotes(t_parsing *parse);
void	ft_handle_dollar_in_str(t_parsing *parse);
char	*ft_handle_dollar_in_heredoc(t_parsing *parse, char *src);
void	ft_update_oldpwd(t_parsing *parse, char *cwd);
void	ft_update_pwd(t_parsing *parse, char *cwd);
char	*ft_loop_tild_hyphen(t_parsing *parse, char c);
void	ft_retrieve_env(t_parsing *parse, char **env);
char	**ft_lst_env_to_tab(t_list *lst);
int		check_builtin_input(t_parsing * parse);
void	execute_built_in(t_parsing *parse);
int		parsing_built_in(t_parsing *parse);
void	input_redirection(t_list **parse);
void	output_redirection(t_list **parse);
void	ft_append(t_list **parse);
void	check_herringbone(t_parsing *parse);
void	ft_unset(t_parsing *parse);
void	ft_exit(t_parsing *parse);
void	ft_print_export(t_parsing *parse);
void	ft_handle_dollar(t_parsing *parse);
void	ft_handle_dollar_in_str(t_parsing *parse);
int		ft_cd(t_parsing *parse);
int		ft_lst_strchr_pipe(t_list *list);
void	cd_in_cmdline(t_parsing *parse);
void	print_list(t_list *list);
void	ft_history(t_parsing *parse);
void	ft_check_history_size(t_parsing *parse);
void	ft_print_history(t_parsing *parse);
void	del_parsed_cmd(t_parsing *parse);
void	pipe_child(t_parsing *parse, int pfd[2]);
void	ft_fill_tmplst(t_parsing *parse, t_list **lst, int start);
char	*ft_set_str_to_comp(char *s);
void	ft_loop(t_parsing *parse, t_list **lst);
void	error_exec_message(t_parsing *parse);
void    ft_return_error(t_parsing *parse);
void	ft_replace_value(t_parsing *parse, t_list **lst);
char	*ft_found_var(t_parsing *parse, char *s);
void	signals_func(void);
void	sig_int(int param);



// void	ft_update_pwd(t_parsing *parse, char *cwd);




#endif
