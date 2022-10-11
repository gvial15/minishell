#PROGRAM NAME-------------------------------------------------------------------

NAME 			= 	minishell

#SYSTEM VAR---------------------------------------------------------------------

R = $(shell tput -Txterm setaf 1)
G = $(shell tput -Txterm setaf 2)
C = $(shell tput -Txterm setaf 6)
W = $(shell tput -Txterm setaf 7)
Y = $(shell tput -Txterm setaf 3)
Z = $(shell tput -Txterm setaf 5)

CFLAGS 			= 	-Wall -Werror -Wextra
CC				= 	gcc
RM				= 	rm -rf
VALG_LEAK		=	valgrind --leak-check=full
UNAME_S		 	= 	$(shell uname -s)
REL_PATH		=	$(shell pwd)
LEAK_CMD		=	leaks --atExit --

READLINEA		=	-lreadline
LIBRARY			=	$(READLINEA) $(LIBFT)

#DIRECTORIES--------------------------------------------------------------------

SRCS_DIR 		= 	./src
OBJS_DIR		= 	./obj
INCLUDE_DIR		=	./include
LIBFT_DIR		= 	$(INCLUDE_DIR)/libft
NAME_DSYM		=	./$(NAME).dSYM

#FILES--------------------------------------------------------------------------

#  To make the list of all src, do this command in terminal in project folder
#  find ./src -type f | cut -c7- | sed 's/$/ \\/'
SRCS_FILES	 	= 	0_main.c \
					01_init.c \
					01_valid_line.c \
					03_format_line.c \
					03_get_cmd_path.c \
					03_get_fd_in_out.c \
					03_parse.c \
					03_utils.c \
					03_utils2.c \
					04_env.c \
					04_env_utils.c \
					05_child_exec.c \
					05_exec.c \
					05_redirection.c \

HEADERS_FILES	=	minishell.h

LIBFT_FILES		= 	libft.a

#FILES VAR----------------------------------------------------------------------
SRCS 			= 	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

HEADERS			=	$(addprefix $(INCLUDE_DIR)/, $(HEADERS_FILES))

OBJS 			= 	$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
OBJS_BONUS 		= 	$(SRCS_BONUS:$(SRCS_DIR_BONUS)/%.c=$(OBJS_DIR_BONUS)/%.o)

LIBFT 			= 	$(addprefix $(LIBFT_DIR)/, $(LIBFT_FILES))

LIBFT_LINUX		=	-L$(REL_PATH)/libft -lft

#SYSTEM RULES-------------------------------------------------------------------

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

#COMPILING RULES------------------------------------------------------------------

all : 				init $(NAME)

init:
					@$(MAKE) -s -C $(LIBFT_DIR)
					@mkdir -p $(OBJS_DIR)

$(NAME):			$(OBJS) 
ifeq ($(UNAME_S),Linux)
					@gcc $(CFLAGS) libft/*c $(SRCS) -o $(NAME) $(READLINEA)
else
					@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBRARY)
endif
					@echo "$G$(NAME)         compiled$W"
					
$(LIBFT):
					@cd $(LIBFT_DIR)/ && make
					

clean:									
					@$(MAKE) -s clean -C $(LIBFT_DIR)
					@$(RM) $(OBJS)
					@$(RM) $(OBJS_DIR)
					@$(RM) $(OBJS_BONUS)
					@$(RM) $(OBJS_DIR_BONUS)
					@echo "$R$(NAME) objects deleted$W"

fclean: 			clean
					@$(MAKE) -s fclean -C $(LIBFT_DIR)				
					@$(RM) $(NAME_DSYM)
					@$(RM) $(NAME)
					@$(RM) $(NAME_BONUS)
					@echo "$R$(NAME)         deleted$W"
	
re: 				fclean all

debug: $(LIBFT)
				gcc -g $(CFLAGS) $(LIBRARY) $(SRCS) -o $(NAME) -D DEBUG=1

#PHONY--------------------------------------------------------------------------

.PHONY:				all clean fclean re init init_bonus debug

