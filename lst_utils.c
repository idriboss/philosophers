#include "philo.h"

void	ft_lstclear(t_philo **lst)
{
	t_philo	*elm;
	t_philo	*tmp;

	elm = *lst;
	while (elm)
	{
		tmp = elm->next;
		pthread_mutex_destroy(elm->fork_mutex);
		free(elm);
		elm = tmp;
	}
}
