NAME  = pipex.a
LIBFT = libft/libft.a

CC    = cc
FLAGS = -Wall -Wextra -Werror

SRC   = $(shell find . -maxdepth 1 -name '*.c')
OBJS  = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c pipex.h
	$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

$(NAME): $(LIBFT) $(OBJS)
	cp $(LIBFT) $(NAME)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all
