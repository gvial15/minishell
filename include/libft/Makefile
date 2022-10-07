SRCS = 	convert/ft_atoi.c  convert/ft_ltoa.c convert/ft_itoa.c convert/ft_itoa_base.c \
		convert/ft_ltox.c convert/ft_ultox.c convert/ft_split.c convert/ft_toupper.c convert/ft_tolower.c \
		memory/ft_memset.c memory/ft_memcpy.c memory/ft_memmove.c memory/ft_memchr.c \
		memory/ft_memcmp.c memory/ft_bzero.c memory/ft_calloc.c memory/free_split.c \
		string/ft_strlcpy.c string/ft_strlcat.c string/ft_strnstr.c string/ft_strlen.c \
		string/ft_strncmp.c string/ft_strchr.c string/ft_strrchr.c \
		string/ft_strdup.c string/ft_substr.c string/ft_strjoin.c \
		string/ft_striteri.c string/ft_strmapi.c string/ft_strtrim.c \
		print/ft_putchar_fd.c print/ft_putstr_fd.c print/ft_putendl_fd.c \
		print/ft_putnbr_fd.c print/print_int_tab.c print/print_split.c \
		ft_is/ft_isalnum.c ft_is/ft_isalpha.c ft_is/ft_isascii.c \
		ft_is/ft_isdigit.c ft_is/ft_isprint.c \
		ft_printf/ft_printf.c ft_printf/format_and_print.c ft_printf/print_c.c \
		ft_printf/print_u.c ft_printf/print_x.c ft_printf/print_nbr.c \
		ft_printf/print_p.c ft_printf/print_percent.c ft_printf/print_s.c \
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		bubble_sort.c string/ft_strrchr_i.c ft_is/ft_iscmd_char.c


BONUSSRCS = lst/ft_lstnew.c lst/ft_lstadd_front.c lst/ft_lstsize.c lst/ft_lstlast.c \
			lst/ft_lstdelone.c lst/ft_lstclear.c lst/ft_lstiter.c lst/ft_lstadd_back.c lst/ft_lstmap.c \

BONUSOBJ = $(BONUSSRCS:%c=%o)

OBJ = $(SRCS:%c=%o)

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: $(OBJ) $(BONUSOBJ)
	ar rcs $(NAME) $(OBJ) $(BONUSOBJ)

clean:
	rm -f $(OBJ) $(BONUSOBJ) -s

fclean: clean
	rm -f $(NAME) -s

re:	fclean all
