/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:44:42 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/12 17:44:54 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int				i;

	i = 0;
	philo = data->philos;
	if (gettimeofday(&time, NULL) == -1)
		return (EXIT_FAILURE);
	data->start_time = time.tv_sec * 1000000 + time.tv_usec;
	pthread_mutex_lock(&data->check_dead_mutex);
	while (i < data->philos_number)
	{
		pthread_create(&philo[i].thread, NULL, (void *)routine, &philo[i]);
		++i;
	}
	pthread_mutex_unlock(&data->check_dead_mutex);
	if (wait_threads(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	wait_threads(t_data *data)
{
	t_philo	*philo;
	int		i;
	int		status;

	philo = data->philos;
	i = 0;
	status = EXIT_SUCCESS;
	while (i < data->philos_number)
	{
		pthread_join(philo[i].thread, NULL);
		++i;
	}
	return (status);
}
