# Makefile

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I

SRCS = 	srcs/str/ft_split.c \
		srcs/str/ft_strjoin.c \
		srcs/str/ft_strjoin_free_s1.c \
		srcs/str/ft_strjoin_free_s1_s2.c \
		srcs/str/ft_strtrim.c \
		srcs/str/ft_strtrim_free_s1.c \
		srcs/str/ft_substr.c \
		srcs/str/ft_striteri.c \
		srcs/str/ft_strmapi.c \
		srcs/str/ft_strnstr.c \
		srcs/str/ft_strrchr.c \
		srcs/str/ft_itoa.c \
		srcs/str/ft_atoi.c \
		srcs/str/ft_atoi_llu.c \
		srcs/str/ft_atoi_base.c \
	   	srcs/str/ft_strchr.c \
	   	srcs/str/ft_strlcpy.c \
	   	srcs/str/ft_found_char.c \
	   	srcs/str/ft_strlcat.c \
	   	srcs/str/ft_strncmp.c \
	   	srcs/str/ft_strcmp.c \
	   	srcs/str/ft_strscmp.c \
	   	srcs/str/ft_strdup.c \
	   	srcs/str/ft_strdup_free.c \
	   	srcs/str/ft_strlen.c \
	   	srcs/str/ft_bzero.c \
	   	srcs/str/ft_strrev.c \
	   	srcs/str/ft_strcpy.c \
	   	srcs/str/get_next_line.c \
	   	srcs/str/ft_str_chr.c \
	   	srcs/str/ft_str_rchr.c \
	   	srcs/to/ft_tolower.c \
	   	srcs/to/ft_toupper.c \
	   	srcs/str/ft_strstr.c \
	   	srcs/print/ft_putendl_fd.c \
	   	srcs/print/ft_putstr_fd.c \
	   	srcs/print/ft_putchar_fd.c \
	   	srcs/print/ft_putnbr_fd.c \
	   	srcs/print/ft_putendl.c \
	   	srcs/print/ft_putstr.c \
	   	srcs/print/ft_putchar.c \
	   	srcs/print/ft_putnbr.c \
	   	srcs/print/ft_print_strs_array.c \
	   	srcs/print/ft_putnbr_base.c \
	   	srcs/mem/ft_calloc.c \
	   	srcs/mem/ft_memchr.c \
	   	srcs/mem/ft_memmove.c \
	   	srcs/mem/ft_memcmp.c \
	   	srcs/mem/ft_memset.c \
	   	srcs/mem/ft_memcpy.c \
	   	srcs/is/ft_isalpha.c \
	   	srcs/is/ft_isprint.c \
	   	srcs/is/ft_isalnum.c \
	   	srcs/is/ft_isdigit.c \
	   	srcs/is/ft_isascii.c \
	   	srcs/is/ft_isspaces.c \
	   	srcs/is/ft_str_isspaces.c \
	   	srcs/tab/ft_nb_digit.c \
	   	srcs/tab/ft_rev_int_tab.c \
	   	srcs/tab/ft_sort_int_tab.c \
	   	srcs/ft_printf/ft_putstr_ptf.c \
	   	srcs/ft_printf/ft_printf.c \
	   	srcs/ft_printf/ft_flag_linker.c \
	   	srcs/ft_printf/ft_print_x.c \
	   	srcs/ft_printf/ft_print_di.c \
	   	srcs/ft_printf/ft_print_u.c \
	   	srcs/ft_printf/ft_print_p.c \
	   	srcs/free/free_str_tab.c srcs/free/free_int_tab2d.c \
		srcs/linked_list/ft_lstadd_back.c \
		srcs/linked_list/ft_lstadd_front.c \
		srcs/linked_list/ft_lstadd_position.c \
		srcs/linked_list/ft_lstdel_all.c \
		srcs/linked_list/ft_lstdel_back.c \
		srcs/linked_list/ft_lstdel_front.c \
		srcs/linked_list/ft_lstdel_position.c \
		srcs/linked_list/ft_lstdel_actual.c \
		srcs/linked_list/ft_lstlast.c \
		srcs/linked_list/ft_lstnew.c \
		srcs/linked_list/ft_lstprint_from_head.c \
		srcs/linked_list/ft_lstprint_from_tail.c \
		srcs/linked_list/ft_lstprint.c \
		srcs/linked_list/ft_lstcpy.c \
		srcs/linked_list/ft_lst_to_str.c \
		srcs/linked_list/ft_lstdel_current.c \
		srcs/linked_list/ft_sortlst_str.c \
		srcs/linked_list/ft_lst_to_char_tab.c \
		srcs/linked_list/ft_lst_strcmp.c \
		srcs/linked_list/ft_lstsize.c

OBJECT_FILES = $(SRCS:.c=.o)

HEADER = ./


all: $(NAME)
%.o: %.c
	@$(CC) $(CFLAGS) $(HEADER) -c $< -o $(<:.c=.o)
	@printf "$(YELLOW)Compiling $(NAME): << $< >>\033[K\r$(DEFAULT)"

$(NAME): $(OBJECT_FILES)
	@echo "\n"
	@ar rsc $(NAME) $(OBJECT_FILES)
	@echo "$(GREEN)<<<<< libft.a created >>>>>$(DEFAULT)"

clean:
	@echo "$(RED)<<<<< deleting libft obj. files >>>>>$(DEFAULT)"
	@rm -rf $(OBJECT_FILES)

fclean: clean
	@echo "$(RED)<<<<< deleting libft.a >>>>>$(DEFAULT)"
	@rm -rf $(NAME)

re: fclean all
	@echo "$(GREEN)\n<<<<< Make re libft done >>>>>$(DEFAULT)"

#COLORS
RED = \033[3;31m
GREEN = \033[3;32m
YELLOW = \033[3;33m
DEFAULT = \033[0m
