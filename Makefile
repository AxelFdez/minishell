# Makefile

NAME = minishell
LIBFT = libft/
LST = linked_list/
CC = gcc 
CFLAGS = -Wall -Wextra -Werror -g

SRCS =  srcs/minishell.c \
		srcs/ft_parsing.c \
		srcs/ft_error.c \
		srcs/ft_token.c \
		srcs/ft_check_syntax.c \
		srcs/ft_initialization.c \
		srcs/ft_fill_lst.c \
		srcs/ft_sort_env.c \
		srcs/built-in/ft_echo.c \
		srcs/built-in/ft_env.c \
		srcs/built-in/ft_pwd.c \
		srcs/built-in/ft_export.c \
		srcs/built-in/ft_unset.c \
		srcs/built-in/ft_exit.c \
		srcs/built-in/ft_check_built_in.c \
		srcs/built-in/ft_print_export.c \
		srcs/built-in/ft_handle_dollar.c \
		srcs/built-in/ft_cd.c \
		srcs/ft_quotes.c

OBJECT_FILES = $(SRCS:.c=.o)
HEADER = -I./includes

all: $(NAME) 
.c.o:
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $(<:.c=.o)

$(NAME): $(OBJECT_FILES)
	@echo "$(YELLOW)\n<<<<< libft compiling ... >>>>>\n$(DEFAULT)"
	$(MAKE) -C $(LIBFT)
	cp libft/libft.a $(NAME)
	@echo "$(YELLOW)\n<<<<< Creating $(NAME) exec file ! ... >>>>>$(DEFAULT)"
	$(CC) $(CFLAGS) $(HEADER) -o $(NAME) $(SRCS) libft/libft.a -lreadline
	@echo "$(GREEN)\n<<<<< $(NAME) created ! ... >>>>>\n$(DEFAULT)"
#------------------------------------------------------------------------------
clean: 
	@echo "$(RED)\n<<<<< deleting $(NAME) obj. files ! ... >>>>>$(DEFAULT)"
	rm -rf $(OBJECT_FILES)
	$(MAKE) clean -C $(LIBFT)
	@echo "$(GREEN)<<<<< clean from $(NAME) done ! >>>>>\n$(DEFAULT)"
#------------------------------------------------------------------------------
fclean: clean
	@echo "$(RED)<<<<< deleting $(NAME) exec ! >>>>>\n$(DEFAULT)"
	rm -rf $(NAME)
	$(MAKE) fclean -C $(LIBFT)
	@echo "$(GREEN)<<<<< fclean from $(NAME) done ! >>>>>\n$(DEFAULT)"
#------------------------------------------------------------------------------
re: fclean all
	@echo "$(GREEN)\n<<<<< $(NAME) make re done ! >>>>>\n$(DEFAULT)"
#------------------------------------------------------------------------------
 

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m
#------------------------------------------------------------------------------
#DEBUG
# -fsanitize=address
# valgrind --leak-check=full
