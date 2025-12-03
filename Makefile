NAME  = pipex.a
LIBFT = libft/libft.a

CC    = cc
FLAGS = -Wall -Wextra -Werror

SRC   = $(shell find -name '*.c')
OBJS  = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c pipex.h
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

$(NAME): $(LIBFT) $(OBJS)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -rf $(OBJS)
	make -C libft clean

fclean:
	rm -rf $(NAME)
	make -C libft fclean

re: fclean all
