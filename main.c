#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 || argc != 6)
		exit(EXIT_FAILURE);
	init_data(&data);
	parse(argv, &data);
	start_threads(&data);
	
}

int	start_threads(t_data *data)
{
	t_philo			*philo;
	struct timeval	time;
	int	i;

	i = 0;
	philo = data->first_philo;
	if (gettimeofday(&time, NULL) == -1)
		return (EXIT_FAILURE);
	data->start_time = time.tv_sec * 1000000 + time.tv_usec;
	while (i < data->philos_number)
	{
		pthread_create(philo->thread, NULL, routine, &philo);
		philo = philo->next;
		++i;
	}
	if (wait_threads(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
}

int	wait_threads(t_data *data)
{
	t_philo	*philo;
	int		i;
	int		*temp;
	int		status;

	philo = data->first_philo;
	i = 0;
	status = EXIT_SUCCESS;
	while (i < data->philos_number)
	{
		pthread_join(*philo->thread, &temp);
		if (temp == EXIT_FAILURE)
			status = EXIT_FAILURE;
		++i;
	}
	return (status);
}
