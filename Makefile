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

LIBRARY			=	$(LIBRD) -lcurses $(LIBFT)

#DIRECTORIES--------------------------------------------------------------------

SRCS_DIR 		= 	./src
OBJS_DIR		= 	./obj
INCLUDE_DIR		=	./include
LIBFT_DIR		= 	$(INCLUDE_DIR)/libft
LIBRD_DIR		=	$(INCLUDE_DIR)/librd

NAME_DSYM		=	./$(NAME).dSYM

#FILES--------------------------------------------------------------------------

#  To make the list of all src, do this command in terminal in project folder
#  find ./src/*.c -type f | cut -c7- | sed 's/$/ \\/'
SRCS_FILES	 	= 	0_main.c \
					01_init.c \
					01_valid_line.c \
					02_signal.c \
					03_convert_env_var.c \
					03_format_line.c \
					03_get_cmd_path.c \
					03_get_fds.c \
					03_parse.c \
					03_parse_utils.c \
					03_split_cmd.c \
					03_utils2.c \
					04_env.c \
					04_env_utils.c \
					05_child_exec.c \
					05_exec.c \
					05_exec_utils.c \
					05_redirection.c \

HEADERS_FILES	=	minishell.h

LIBFT_FILES		= 	libft.a
LIBRD_FILES		=	libreadline.a \
					libhistory.a


#FILES VAR----------------------------------------------------------------------
SRCS 			= 	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

HEADERS			=	$(addprefix $(INCLUDE_DIR)/, $(HEADERS_FILES))

OBJS 			= 	$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
OBJS_BONUS 		= 	$(SRCS_BONUS:$(SRCS_DIR_BONUS)/%.c=$(OBJS_DIR_BONUS)/%.o)

LIBFT 			= 	$(addprefix $(LIBFT_DIR)/, $(LIBFT_FILES))
LIBRD_MAKEFILE	=	$(addprefix $(LIBRD_DIR)/, Makefile)
LIBRD			=	$(addprefix $(LIBRD_DIR)/, $(LIBRD_FILES))

RD_CONFIG		=	include/librd/Makefile

#SYSTEM RULES-------------------------------------------------------------------

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

#COMPILING RULES------------------------------------------------------------------

all : 				init $(LIBRD_MAKEFILE) $(LIBRD) $(NAME)

$(LIBRD): 			$(LIBRD_MAKEFILE)
					@$(MAKE) -s -C $(LIBRD_DIR) --silent
					@echo "$GReadline's libraries compiled$W"

$(LIBRD_MAKEFILE):
					@cd $(LIBRD_DIR) && ./configure --silent
					@echo "$GReadline          configured$W"

init:
					@$(MAKE) -s -C $(LIBFT_DIR)
					@mkdir -p $(OBJS_DIR)
					

$(NAME):			$(OBJS) 
					@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBRARY)
					@echo "$G$(NAME)         compiled$W"
					
$(LIBFT):
					@cd $(LIBFT_DIR)/ && make
					

clean:									
					@$(MAKE) -s clean -C $(LIBFT_DIR)
					@$(RM) $(OBJS)
					@$(RM) $(OBJS_DIR)
					@$(RM) $(OBJS_BONUS)
					@$(RM) $(OBJS_DIR_BONUS)
					@echo "$R$ All objects       deleted$W"

fclean: 			clean
					@$(MAKE) -s fclean -C $(LIBFT_DIR)
					@$(MAKE) -s clean -C $(LIBRD_DIR)
					@$(RM) $(NAME_DSYM)
					@$(RM) $(NAME)
					@$(RM) $(NAME_BONUS)
					@echo "$R$(NAME) & lib   deleted$W"

reset:				fclean
					@$(MAKE) -s distclean -C $(LIBRD_DIR)
					@echo "$R$ readline lib      reseted$W"

re: 				fclean all

debug: $(LIBFT)
				gcc -g $(CFLAGS) $(LIBRARY) $(SRCS) -o $(NAME) -D DEBUG=1

#PHONY--------------------------------------------------------------------------

.PHONY:				all clean fclean re init debug reset

