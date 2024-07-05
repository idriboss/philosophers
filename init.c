#include "philo.h"

int	init_data(t_data *data)
{
	pthread_mutex_t	*printf_mutex;

	memset(data, 0, sizeof(t_data));
	data->first_philo = init_philos;
	if (data->first_philo == NULL)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(printf_mutex, NULL) != 0)
		return (EXIT_FAILURE);
	data->printf_mutex = printf_mutex;
}

t_philo	*init_philos(t_data *data)
{
	t_philo	*first;
	t_philo	*temp;
	int		i;

	first = create_philo(0, NULL, data);
	if (first == NULL)
		return (NULL);
	temp = first;
	i = 0;
	while (++i < data->philos_number - 1) 
	{
		temp->next = create_philo(i, temp, data);
		if (temp == NULL)
		{
			ft_lstclear(&first);
			return (NULL);
		}
		temp->next->before = temp;
		temp = temp->next;
	}
	temp->next = first;
	first->before = temp;
	return (first);
}

t_philo	*create_philo(int	id, t_philo *before, t_data *data)
{
	t_philo			*philo;
	pthread_mutex_t	*fork;

	philo = malloc(sizeof(t_philo) * 1);
	if (philo == NULL)
		return (NULL);
	if (pthread_mutex_init(fork, NULL) != EXIT_SUCCESS)
		return (NULL);
	memset(philo, 0, sizeof(t_philo));
	philo->fork_mutex = fork;
	philo->id = id;
	philo->before = before;
}
