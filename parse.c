#include "philo.h"

void	parse(char **argv, t_data *data)
{
	data->philos_number = ft_atol(argv[1], data);
	if (data->philos_number < 1)
		free_and_exit("Error: bad inputs", EXIT_FAILURE, data);
	data->time_to_die = ft_atol(argv[2], data);
	data->time_to_eat = ft_atol(argv[3], data);
	data->time_to_sleep = ft_atol(argv[4], data);
	if (argv[5] != NULL)
		data->must_eat = ft_atol(argv[5], data);
	else
		data->must_eat = -1;
}
