/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chmassa <chmassa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:32:08 by axfernan          #+#    #+#             */
/*   Updated: 2023/04/21 12:06:36 by chmassa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}			t_cmd;

typedef struct s_sig
{
	int		child;
	int		heredoc;
	int		int_heredoc;
	int		return_value;
	int		child_heredoc;
}			t_sig;

typedef struct s_pipex
{
	int		sep;
	int		*children;
	int		i;
	int		last_cmd_value_return;
	int		last_cmd_no;
}			t_pipex;

extern t_sig	g_sig;

typedef struct s_parsing
{
	int				is_in_str;
	int				ret_value;
	int				tmp_ret_value;
	int				i;
	int				i_b;
	int				j;
	int				k;
	int				fd_history[2];
	int				is_dollar;
	char			*str_tmp;
	char			var_name[1024];
	char			c;
	char			pwd_save[1024];
	char			*lex[11];
	char			*meta[6];
	char			*non_bl_chars;
	char			*s1;
	char			*s2;
	char			tmp_input[1024];
	int				len;
	int				len_b;
	int				quote_to_del;
	char			*input;
	char			*prompt;
	char			**env;
	t_list			*lst_cmdline;
	t_list			*lst_env;
	char			**command;
	int				lst_target;
	int				built_in_cmd;
	int				redirection_out;
	int				redirection_in;
	struct termios	term;
	int				temp_fd;
	int				status;
	int				fd_stdin;
	int				fd_stdout;
	int				heredoc_pfd;
	int				heredoc_status;
	char			**heredoc_tab;
	int				heredoc_count;
}				t_parsing;

//**** signals ****************************************************************
void	handle_signals(int sig);
void	signals_(int heredoc);
void	signals_func(void);
void	sig_int(int param);
//**** execution **************************************************************
void	ft_main_loop(t_parsing *parse);
int		is_pipe(t_parsing *parse);
void	execute_cmd(t_parsing *parse);
void	execute_built_in(t_parsing *parse);
int		count_pipe(t_list *list);
void	one_pipe(t_parsing *parse);
void	pipex(t_parsing *parse);
int		check_builtin_input(t_parsing *parse);
int		ft_lst_strchr_pipe(t_list *list);
void	input_redirection(t_list **parse);
void	output_redirection(t_list **parse);
void	error_exec_message(t_parsing *parse);
void	check_herringbone(t_parsing *parse);
void	check_heredoc(t_parsing *parse);
void	ft_heredoc(t_parsing *parse, t_list **lst);
int		check_herringbones_input(t_parsing *parse);
void	parsing_command_child(t_parsing *parse);
void	execute_command_child(t_parsing *parse);
void	delete_cmd(t_list **list_cmd);
void	multi_pipes(t_parsing *parse, t_pipex *pipex);
void	command_father(t_parsing *parse);
//**** parsing ****************************************************************
void	ft_strdel_quotes(t_parsing *parse, char *str);
void	ft_parsing(char *input);
int		ft_get_cmdline(t_parsing *parse);
void	ft_quotes(t_parsing *parse);
int		parsing_built_in(t_parsing *parse);
void	ft_fill_lst(t_list **lst, t_parsing *parse, int start);
int		is_close_herringbone(t_parsing *parse);
int		ft_lexer(t_parsing *parse);
int		is_open_herringbone(t_parsing *parse);
void	ft_initialization(t_parsing *parse);
int		is_meta_char(int c);
void	parsing_cmd(t_parsing *parse);
int		ft_lst_strchr_meta(t_list *list);
void	rl_replace_line(const char *text, int clear_undo);
void	ft_error(char *err_mess);
void	error_exec_message(t_parsing *parse);
void	ft_init_lexer(t_parsing *parse);
void	ft_increment(t_parsing *parse, char c);
int		ft_len_str_to_cmp(t_parsing *parse);
char	*ft_fill_str_to_cmp(t_parsing *parse, char *s);
int		ft_check_double_pipes(t_list *lst);
void	is_quote_string(t_parsing *parse, char c);
void	is_no_quote_string(t_parsing *parse);
//**** built-in ***************************************************************
void	ft_check_built_in(t_parsing *parse);
void	ft_echo(t_list *tmp, t_parsing *parse);
void	built_in_used_alone(t_parsing *parse);
void	execute_built_in_alone(t_parsing *parse);
int		parsing_built_in(t_parsing *parse);
int		check_builtin_input(t_parsing *parse);
//**** ft_export/ft_unset *****************************************************
int		ft_export(t_parsing *parse);
void	ft_sort_env(t_list **lst);
void	ft_print_sorted_env(t_parsing *parse);
void	ft_print_export(t_parsing *parse);
void	ft_fill_tmplst(t_parsing *parse, t_list **lst, int start);
void	ft_unset(t_parsing *parse);
//**** ft_history *************************************************************
void	ft_history(t_parsing *parse);
void	ft_check_history_size(t_parsing *parse);
void	ft_print_history(t_parsing *parse);
void	ft_add_history(t_parsing *parse);
//**** ft_cd ******************************************************************
int		ft_cd(t_parsing *parse);
void	cd_in_cmdline(t_parsing *parse);
//**** dollar *****************************************************************
void	ft_handle_dollar_no_quotes(t_parsing *parse);
void	ft_handle_dollar_in_str(t_parsing *parse);
char	*ft_handle_dollar_in_heredoc(t_parsing *parse, char *src);
void	ft_replace_value(t_parsing *parse, t_list **lst);
void	ft_handle_dollar(t_parsing *parse);
void	ft_loop_dollar(t_parsing *parse, t_list **lst);
//**** ft_env *****************************************************************
int		ft_env(t_parsing *parse);
void	ft_retrieve_env(t_parsing *parse, char **env);
char	**ft_lst_env_to_tab(t_list *lst);
//**** ft_pwd *****************************************************************
int		ft_pwd(void);
void	ft_update_oldpwd(t_parsing *parse, char *cwd);
void	ft_update_pwd(t_parsing *parse, char *cwd);
char	*ft_loop_tild_hyphen(t_parsing *parse, char c);
char	*ft_get_current_position(void);
void	ft_exit(t_parsing *parse);
void	print_list(t_list *list);
void	del_parsed_cmd(t_parsing *parse);
char	*ft_set_str_to_comp(char *s);
void	ft_return_error(t_parsing *parse);
//**** environnement **********************************************************
char	*ft_found_var(t_parsing *parse, char *s);
void	ft_handle_shlvl(t_parsing *parse);
void	ft_handle_underscore(t_parsing *parse);
void	ft_replace_underscore_value(t_list *lst, char *s);
#endif
