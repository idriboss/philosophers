#	colors	#

BLACK=	$(shell tput -Txterm setaf 0)
RED= 	$(shell tput -Txterm setaf 1)
GREEN= 	$(shell tput -Txterm setaf 2)
WHITE= 	$(shell tput -Txterm setaf 7)
YELLOW=	$(shell tput -Txterm setaf 3)
BLUE=	$(shell tput -Txterm setaf 6)
END= 	$(shell tput -Txterm sgr0)

#			#

NAME = philo

CC = cc

FLAGS = -Wall -Werror -Wextra -pthread

LIBS = philo.h

FILES =		parse.c		\
			main.c		\
			utils.c		\
			routine.c	\
			lst_utils.c	\
			init.c		\
			error.c		\
			utils2.c	\

OBJ_DIR = objs/

OBJ = $(FILES:.c=.o)

OBJ_PREFIXED = $(addprefix $(OBJ_DIR), $(OBJ))

all	: Makefile $(NAME)

$(NAME) : $(OBJ_PREFIXED)
		@$(CC) $(FLAGS) $(OBJ_PREFIXED) -o $(NAME)
		@echo "$(GREEN)$(NAME) done ! ✅$(END)"

$(OBJ_DIR)%.o : %.c $(LIBS)
		@mkdir -p $(OBJ_DIR)
		@echo "$(BLUE)Compiling: $^$(END)"
		@$(CC) $(FLAGS) -c $< -o $@
