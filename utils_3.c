#include "philo.h"

void	set_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->check_dead_mutex);
	philo->data->check_dead = true;
	pthread_mutex_unlock(&philo->data->check_dead_mutex);
}

bool	get_dead(t_philo *philo)
{
	bool	check_dead;

	pthread_mutex_lock(&philo->data->check_dead_mutex);
	check_dead = philo->data->check_dead;
	pthread_mutex_unlock(&philo->data->check_dead_mutex);
	return (check_dead);
}
