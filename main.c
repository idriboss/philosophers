#include "philo.h"

int	start_threads(t_data *data);
int	wait_threads(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc != 5 && argc != 6)
		exit(EXIT_FAILURE);
	if (parse(argv, &data) == -1)
		return (EXIT_FAILURE);
	if (init_data(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (start_threads(&data) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
		pthread_create(philo->thread, NULL, (void *)routine, philo);
		philo = philo->next;
		++i;
	}
	if (wait_threads(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	wait_threads(t_data *data)
{
	t_philo	*philo;
	t_philo	*temp;
	int		i;
	// int		*temp;
	int		status;

	philo = data->first_philo;
	i = 0;
	status = EXIT_SUCCESS;
	while (i < data->philos_number)
	{
		pthread_join(*philo->thread, NULL);
		// if (*temp == EXIT_FAILURE)
		// 	status = EXIT_FAILURE;
		temp = philo;
		philo = philo->next;
		free(temp);
		++i;
	}
	return (status);
}
