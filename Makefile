#	colors	#

BLACK=	$(shell tput -Txterm setaf 0)
RED= 	$(shell tput -Txterm setaf 1)
GREEN= 	$(shell tput -Txterm setaf 2)
WHITE= 	$(shell tput -Txterm setaf 7)
YELLOW=	$(shell tput -Txterm setaf 3)
BLUE=	$(shell tput -Txterm setaf 6)
END= 	$(shell tput -Txterm sgr0)

#			#

MANDATORY_DIR = mandatory/

MANDATORY_FILES = 	mandatory/main.c	\
					mandatory/error.c	\
					mandatory/init.c	\
					mandatory/Makefile	\
					mandatory/parse.c	\
					mandatory/routine.c	\
					mandatory/utils_1.c	\
					mandatory/utils_2.c	\
					mandatory/utils_3.c	\
					mandatory/philo.h	\

BONUS_DIR = bonus/

all	: mandatory bonus

mandatory : ./philo $(MANDATORY_DIR)
	@make -sC $(MANDATORY_DIR)
	@echo "$(GREEN)philo done ! ✅$(END)"

mandatory_clean :
	@make clean -sC $(MANDATORY_DIR)

mandatory_fclean :
	@make fclean -sC $(MANDATORY_DIR)

Bonus : ./philo $(BONUS_DIR)
	@make -sC $(BONUS_DIR)
	@echo "$(GREEN)philo done ! ✅$(END)"

bonus_clean :
	@make clean -sC $(BONUS_DIR)

bonus_fclean :
	@make fclean -sC $(BONUS_DIR)

clean :
	@echo "$(YELLOW)Mandatory:$(END)"
	@echo ""
	@make -s mandatory_clean
	@echo ""
	@echo "$(YELLOW)Bonus:$(END)"
	@echo ""
	@make -s bonus_clean

fclean :
	@echo "$(YELLOW)Mandatory:$(END)"
	@echo ""
	@make -s mandatory_fclean
	@echo ""
	@echo "$(YELLOW)Bonus:$(END)"
	@echo ""
	@make -s bonus_fclean

re : fclean all

.PHONY: all re clean fclean