CC			= cc

NAME		= philo

SRC			= main.c init.c exit_error.c utils.c thanatos.c philo.c

OBJ			:= $(SRC:.c=.o)

CFLAGS		= -Wextra -Wall -Werror

HEADERS		= -I.

all			: $(NAME)

$(NAME)		: $(OBJ)
		$(CC) $(CFLAGS) $^ -o $@

%.o			: %.c
		$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean		:
		rm -f $(OBJ)

fclean		: clean
		rm -f $(NAME)

re			: fclean all

.PHONY		: all clean fclean re
