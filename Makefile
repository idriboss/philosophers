#	colors	#

BLACK=	$(shell tput -Txterm setaf 0)
RED= 	$(shell tput -Txterm setaf 1)
GREEN= 	$(shell tput -Txterm setaf 2)
WHITE= 	$(shell tput -Txterm setaf 7)
YELLOW=	$(shell tput -Txterm setaf 3)
BLUE=	$(shell tput -Txterm setaf 6)
END= 	$(shell tput -Txterm sgr0)

#			#

MANDATORY = philo

MANDATORY_DIR = mandatory/

MANDATORY_FILES = 	mandatory/monitoring.c	\
					mandatory/error.c		\
					mandatory/init.c		\
					mandatory/Makefile		\
					mandatory/parse.c		\
					mandatory/routine.c		\
					mandatory/utils_1.c		\
					mandatory/utils_2.c		\
					mandatory/utils_3.c		\
					mandatory/utils_4.c		\
					mandatory/philo.h		\

BONUS = philo_bonus

BONUS_DIR = bonus/

BONUS_FILES = 		bonus/monitoring.c	\
					bonus/error.c		\
					bonus/init.c		\
					bonus/Makefile		\
					bonus/parse.c		\
					bonus/routine.c		\
					bonus/utils_1.c		\
					bonus/utils_2.c		\
					bonus/utils_3.c		\
					bonus/utils_4.c		\
					bonus/philo.h		\

all	: $(MANDATORY) $(BONUS)

$(MANDATORY) :
	@echo "$(YELLOW)Mandatory:$(END)"
	@echo ""
	@make -sC $(MANDATORY_DIR)
	@echo "$(GREEN)$(MANDATORY) done ! ✅$(END)"
	@echo ""

$(BONUS) :
	@echo "$(YELLOW)Bonus:$(END)"
	@echo ""
	@make -sC $(BONUS_DIR)
	@echo "$(GREEN)$(BONUS) done ! ✅$(END)"
	@echo ""

clean :
	@echo "$(YELLOW)Mandatory:$(END)"
	@echo ""
	@make clean -sC $(MANDATORY_DIR)
	@echo ""
	@echo "$(YELLOW)Bonus:$(END)"
	@echo ""
	@make clean -sC $(BONUS_DIR)
	@echo ""

fclean :
	@echo "$(YELLOW)Mandatory:$(END)"
	@echo ""
	@make fclean -sC $(MANDATORY_DIR)
	@echo ""
	@echo "$(YELLOW)Bonus:$(END)"
	@echo ""
	@make fclean -sC $(BONUS_DIR)
	@echo ""

re :
	@echo "$(YELLOW)Mandatory:$(END)"
	@echo ""
	@make re -sC $(MANDATORY_DIR)
	@echo ""
	@echo "$(YELLOW)Bonus:$(END)"
	@echo ""
	@make re -sC $(BONUS_DIR)
	@echo ""

.PHONY: all re clean fclean