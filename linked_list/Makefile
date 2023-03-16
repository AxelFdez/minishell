# Makefile

NAME = lst.a
CC = gcc 
CFLAGS = -Wall -Wextra -Werror -I

SRCS =  ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstadd_position.c \
		ft_lstdel_all.c \
		ft_lstdel_back.c \
		ft_lstdel_front.c \
		ft_lstdel_position.c \
		ft_lstlast.c \
		ft_lstnew.c \
		ft_lstprint_from_head.c \
		ft_lstprint_from_tail.c \
		lstprint.c \
		ft_lstcpy.c \
		ft_lstsize.c

			

OBJECT_FILES = $(SRCS:.c=.o)

HEADER = ./

all: $(NAME) 

.c.o:
	$(CC) $(CFLAGS) $(HEADER) -c  $< -o $(<:.c=.o)

$(NAME): $(OBJECT_FILES)
	ar rsc $(NAME) $(OBJECT_FILES)
	@echo "\n"
	@echo "\033[92m<<<<< $(NAME) created ! >>>>>\033[0m"

clean:
	rm -rf $(OBJECT_FILES)
	@echo "\n"
	@echo "\033[92m<<<<< object files cleaned ! >>>>>\033[0m"

fclean: clean
	rm -rf $(NAME)
	@echo "\033[92m<<<<< fclean done ! >>>>>\033[0m"

re: fclean all
	@echo "\033[92m<<<<< Make re done ! >>>>>\033[0m"
