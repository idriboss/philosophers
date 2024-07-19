/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:44:42 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/19 16:05:39 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		start_threads(t_data *data);
int		wait_threads(t_data *data);
bool	check_philos(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc != 5 && argc != 6)
		exit(EXIT_FAILURE);
	if (parse(argv, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_data(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (data.philos_number == 1)
		start_solo_philo(&data);
	else if (start_threads(&data) == -1)
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
	pthread_mutex_lock(&data->printf_mutex);
	while (i < data->philos_number)
	{
		pthread_create(&philo[i].thread, NULL, (void *)routine, &philo[i]);
		++i;
	}
	pthread_mutex_unlock(&data->printf_mutex);
	check_philos(data);
	if (wait_threads(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

bool	check_philos(t_data *data)
{
	int		i;
	t_philo	*philo;	

	philo = data->philos;
	while (1)
	{
		i = -1;
		while (++i < data->philos_number)
		{
			if (get_time(&philo[i]) - get_last_eat(&philo[i])
				> data->time_to_die)
			{
				pthread_mutex_lock(&philo->data->printf_mutex);
				pthread_mutex_lock(&philo[i].check_dead_mutex);
				set_dead_philo(&philo[i]);
				return (kill_all_philos(philo, &philo[i]), true);
			}
			if (data->must_eat != -1 && check_eat(philo) == true)
			{
				pthread_mutex_lock(&philo[i].check_dead_mutex);
				return (end_philos(data, &philo[i]), true);
			}
			usleep(5);
		}
	}
}

void	kill_all_philos(t_philo *philos, t_philo *locked_philo)
{
	int		i;
	int		philo_number;
	long	time;

	time = get_time(philos);
	philo_number = philos->data->philos_number;
	i = -1;
	while (++i < philo_number)
	{
		if (&philos[i] != locked_philo)
			pthread_mutex_lock(&philos[i].check_dead_mutex);
	}
	printf("%li	%d	died\n", time / 1000, get_dead_philo(philos)->id + 1);
	i = -1;
	while (++i < philo_number)
	{
		philos[i].dead = true;
	}
	i = -1;
	pthread_mutex_unlock(&philos->data->printf_mutex);
	while (++i < philo_number)
		pthread_mutex_unlock(&philos[i].check_dead_mutex);
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
