SRC =	main.c src/get_cmd_path.c src/get_cmds.c src/exec.c \
		src/utils.c src/builtins.c \

OBJ = $(SRC:%c=%o)

CC = gcc

# CFLAGS = -Wall -Werror -Wextra | muted for testing purpose

NAME = ms

RM = rm -rf

MAKELIBFT = cd libft && make -s

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKELIBFT)
	$(CC) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

clean:
# cd libft && make clean -s
	$(RM) $(OBJ)

fclean: clean
	cd libft && make fclean -s
	$(RM) $(NAME)

re: fclean all

