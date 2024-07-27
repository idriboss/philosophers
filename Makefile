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

BONUS_FILES = 	bonus/checkers.c	\
				bonus/error.c	\
				bonus/init.c	\
				bonus/Makefile	\
				bonus/monitoring.c	\
				bonus/parse.c	\
				bonus/philo_monitor.c	\
				bonus/philo_bonus.h	\
				bonus/routine_utils.c	\
				bonus/routine.c	\
				bonus/solo_philo.c	\
				bonus/utils.c	\

all	: $(MANDATORY) $(BONUS)

$(MANDATORY) : $(MANDATORY_FILES)
	@echo ""
	@echo "$(YELLOW)Mandatory:$(END)"
	@echo ""
	@make -sC $(MANDATORY_DIR)
	@echo ""
	@echo "$(GREEN)$(MANDATORY) done ! ✅$(END)"
	@echo ""

$(BONUS) : $(BONUS_FILES)
	@echo "$(YELLOW)Bonus:$(END)"
	@echo ""
	@make -sC $(BONUS_DIR)
	@echo ""
	@echo "$(GREEN)$(BONUS) done ! ✅$(END)"
	@echo ""

clean :
	@clear
	@echo "$(YELLOW)Mandatory:$(END)"
	@echo ""
	@make clean -sC $(MANDATORY_DIR)
	@echo ""
	@echo "$(YELLOW)Bonus:$(END)"
	@echo ""
	@make clean -sC $(BONUS_DIR)
	@echo ""

fclean :
	@clear
	@echo "$(YELLOW)Mandatory:$(END)"
	@echo ""
	@make fclean -sC $(MANDATORY_DIR)
	@echo ""
	@echo "$(YELLOW)Bonus:$(END)"
	@echo ""
	@make fclean -sC $(BONUS_DIR)
	@echo ""

re :
	@clear
	@echo "$(YELLOW)Mandatory:$(END)"
	@echo ""
	@make re -sC $(MANDATORY_DIR)
	@echo ""
	@echo "$(GREEN)$(MANDATORY) done ! ✅$(END)"
	@echo ""
	@echo "$(YELLOW)Bonus:$(END)"
	@echo ""
	@make re -sC $(BONUS_DIR)
	@echo ""
	@echo "$(GREEN)$(BONUS) done ! ✅$(END)"
	@echo ""

.PHONY: all re clean fclean