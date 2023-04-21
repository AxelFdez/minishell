# Makefile

NAME = minishell
LIBFT = libft/
LST = linked_list/
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LRFLAGS = -L $(shell ./readline_path.sh)
SRCS =  srcs/minishell.c \
		srcs/ft_parsing.c \
		srcs/ft_error.c \
		srcs/ft_token.c \
		srcs/ft_lexer.c \
		srcs/ft_lexer_utils.c \
		srcs/ft_initialization.c \
		srcs/ft_fill_lst.c \
		srcs/ft_signals.c \
		srcs/is_meta_char.c \
		srcs/ft_execute.c \
		srcs/ft_handle_env.c \
		srcs/ft_history.c \
		srcs/ft_pipex.c \
		srcs/ft_pipex_utils.c \
		srcs/ft_pipex_utils2.c \
		srcs/ft_pipex_multi_pipe.c \
		srcs/ft_herringbone.c \
		srcs/ft_sort_env.c \
		srcs/ft_handle_shlvl.c \
		srcs/ft_handle_underscore.c \
		srcs/ft_heredoc.c \
		srcs/ft_check_herringbone.c \
		srcs/ft_is_quote_string.c \
		srcs/ft_is_no_quote_string.c \
		srcs/built-in/ft_echo.c \
		srcs/built-in/ft_env.c \
		srcs/built-in/ft_pwd.c \
		srcs/built-in/ft_export.c \
		srcs/built-in/ft_unset.c \
		srcs/built-in/ft_exit.c \
		srcs/built-in/ft_check_built_in.c \
		srcs/built-in/ft_print_export.c \
		srcs/built-in/ft_handle_dollar.c \
		srcs/built-in/ft_handle_dollar_in_str.c \
		srcs/built-in/ft_handle_dollar_utils.c \
		srcs/built-in/ft_handle_dollar_utils_2.c \
		srcs/built-in/ft_cd.c \
		srcs/built-in/ft_cd_utils.c \
		srcs/built-in/ft_handle_dollar_in_heredoc.c \
		srcs/ft_quotes.c
OBJECT_FILES = $(SRCS:.c=.o)
HEADER = -I./includes

all: $(NAME)
.c.o:
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $(<:.c=.o)
	@printf "$(YELLOW)Compiling $(NAME): << $< >>\033[K\r$(DEFAULT)"

$(NAME): $(OBJECT_FILES)
	@echo "\n"
	@$(MAKE) -C $(LIBFT)
	@$(CC) $(CFLAGS) $(HEADER) -o $(NAME) $(SRCS) libft/libft.a $(LRFLAGS) -lreadline #-fsanitize=address
	@echo "$(GREEN)<<<<< $(NAME) exec file created >>>>>$(DEFAULT)"
#------------------------------------------------------------------------------
clean:
	@echo "$(RED)<<<<< deleting $(NAME) obj. files >>>>>$(DEFAULT)"
	@rm -rf $(OBJECT_FILES)
	@$(MAKE) clean -C $(LIBFT)
	@echo "$(GREEN)<<<<< clean from $(NAME) done >>>>>\n$(DEFAULT)"
#------------------------------------------------------------------------------
fclean: clean
	@echo "$(RED)<<<<< deleting $(NAME) exec >>>>>$(DEFAULT)"
	@rm -rf $(NAME)

	@$(MAKE) fclean -C $(LIBFT)
	@echo "$(GREEN)<<<<< fclean from $(NAME) done >>>>>\n$(DEFAULT)"
#------------------------------------------------------------------------------
re: fclean all
	@echo "$(GREEN)\n<<<<< $(NAME) make re done >>>>>$(DEFAULT)"
#------------------------------------------------------------------------------
#COLORS
RED = \033[3;31m
GREEN = \033[3;32m
YELLOW = \033[3;33m
DEFAULT = \033[0m
#------------------------------------------------------------------------------
#DEBUG
# -fsanitize=address
# valgrind --leak-check=full
