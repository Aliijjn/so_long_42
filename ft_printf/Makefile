SRC = ft_printf.c print_hex.c print_nbr.c print_str.c print_chr.c

LIBFTPATH = ./../libft/

LIBFT = $(LIBFTPATH)libft.a

CFLAGS = -Werror -Wall -Wextra

OBJ = $(SRC:.c=.o)

NAME = libftprintf.a

$(NAME) : $(OBJ) $(LIBFT)
	cp $(LIBFT) $(NAME)
	ar -rsc $(NAME) $(OBJ)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:
	all clean fclean re