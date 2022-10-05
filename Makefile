#PROGRAM NAME-------------------------------------------------------------------

NAME 			= 	minishell
#NAME_BONUS		=	$(NAME)_bonus

#OPTIONS------------------------------------------------------------------------

#PROJECT HAVE (no:n yes:y)
#HAVE_LIBFT		= y

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
SRC_LIST		=	$(shell find ./src -type f | cut -c7- | sed 's/$/ \\/' )


#DIRECTORIES--------------------------------------------------------------------

SRCS_DIR 		= 	./src
OBJS_DIR		= 	./obj
INCLUDE_DIR		=	./include
LIBFT_DIR		= 	$(INCLUDE_DIR)/libft
NAME_DSYM		=	./$(NAME).dSYM

#SRCS_DIR_BONUS	= 	./bonus/src
#OBJS_DIR_BONUS	= 	./bonus/obj

#FILES--------------------------------------------------------------------------

#find ./src -type f | cut -c7- | sed 's/$/ \\/'
SRCS_FILES	 	= 	0_main.c \
					

HEADERS_FILES	=	minishell.h

#SRCS_FILES_BONUS= 	

LIBFT_FILES		= 	libft.a

#FILES VAR----------------------------------------------------------------------
SRCS 			= 	$(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
#SRCS_BONUS		=	$(addprefix $(SRCS_DIR_BONUS)/, $(SRCS_FILES_BONUS))

HEADERS			=	$(addprefix $(INCLUDE_DIR)/, $(HEADERS_FILES))

OBJS 			= 	$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
OBJS_BONUS 		= 	$(SRCS_BONUS:$(SRCS_DIR_BONUS)/%.c=$(OBJS_DIR_BONUS)/%.o)

LIBFT 			= 	$(addprefix $(LIBFT_DIR)/, $(LIBFT_FILES))

LIBFT_LINUX		=	-L$(REL_PATH)/libft -lft

#SYSTEM RULES-------------------------------------------------------------------

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

#$(OBJS_DIR_BONUS)/%.o: $(SRCS_DIR_BONUS)/%.c
#	@$(CC) $(CFLAGS) -c $< -o $@

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
ifneq ($(wildcard $(OBJS_DIR)),)									
					@$(MAKE) -s clean -C $(LIBFT_DIR)
					@$(RM) $(OBJS)
					@$(RM) $(OBJS_DIR)
					@$(RM) $(OBJS_BONUS)
					@$(RM) $(OBJS_DIR_BONUS)
					@echo "$R$(NAME) objects deleted$W"
endif

fclean: 			clean
ifneq ($(wildcard $(NAME)),)					
					@$(MAKE) -s fclean -C $(LIBFT_DIR)
					@$(RM) $(NAME_DSYM)
					@$(RM) $(NAME)
					@$(RM) $(NAME_BONUS)
					@echo "$R$(NAME)         deleted$W"
endif
	
re: 				fclean all

#bonus:				init_bonus $(NAME_BONUS)

#init_bonus:
#					@$(MAKE) -s -C $(LIBFT_DIR)
#					@mkdir -p $(OBJS_DIR_BONUS)

#$(NAME_BONUS):		$(OBJS_BONUS)
#					@gcc $(CFLAGS) libft/*c $(SRCS_BONUS) -o $(NAME_BONUS)
#					@echo "$G$(NAME_BONUS) compiled$W"

debug:
ifeq ($(HAVE_LIBFT),y)
					gcc -g $(CFLAGS) libft/*c $(SRCS) -o $(NAME)
else
					gcc -g $(CFLAGS) $(SRCS) -o $(NAME)
endif

#PHONY--------------------------------------------------------------------------

.PHONY:				all clean fclean re bonus init init_bonus debug

