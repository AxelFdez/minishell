# Makefile

NAME = minishell
LIBFT = libft/
LST = linked_list/
CC = gcc 
CFLAGS = -Wall -Wextra -Werror

SRCS =  srcs/minishell.c \
		srcs/ft_parsing.c \
		srcs/ft_error.c \
		srcs/ft_token.c \
		srcs/ft_check_syntax.c \
		srcs/ft_initialization.c \
		srcs/ft_fill_lst.c \
		srcs/built-in/ft_echo.c \
		srcs/ft_quotes.c

OBJECT_FILES = $(SRCS:.c=.o)
HEADER = -I./includes

all: $(NAME) 
.c.o:
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $(<:.c=.o)

$(NAME): $(OBJECT_FILES)
	@echo "$(YELLOW)\n<<<<< libft compiling ... >>>>>\n$(DEFAULT)"
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(LST)
	cp linked_list/lst.a $(NAME)
	cp libft/libft.a $(NAME)
	@echo "$(YELLOW)\n<<<<< Creating $(NAME) exec file ! ... >>>>>$(DEFAULT)"
	$(CC) $(CFLAGS) $(HEADER) -o $(NAME) $(SRCS) libft/libft.a linked_list/lst.a -lreadline
	@echo "$(GREEN)\n<<<<< $(NAME) created ! ... >>>>>\n$(DEFAULT)"
#------------------------------------------------------------------------------
clean: 
	@echo "$(RED)\n<<<<< deleting $(NAME) obj. files ! ... >>>>>$(DEFAULT)"
	rm -rf $(OBJECT_FILES)
	@echo "$(GREEN)<<<<< clean from $(NAME) done ! >>>>>\n$(DEFAULT)"
	$(MAKE) clean -C $(LIBFT)
	$(MAKE) clean -C $(LST)
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
