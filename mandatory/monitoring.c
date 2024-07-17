/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:44:42 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/17 15:41:15 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(t_data *data);
int	wait_threads(t_data *data);
void	check_philos(t_data *data);

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

void	check_philos(t_data *data)
{
	int		i;
	t_philo	*philo;	
	
	philo = data->philos;
	while (1)
	{
		i = -1;
		while (++i < data->philos_number)
		{
			pthread_mutex_lock(&philo[i].check_dead_mutex);
			if (get_time(&philo[i]) - get_last_eat(&philo[i])
				> data->time_to_die)
			{
				set_dead_philo(&philo[i]);
				// printf("[DEBUG: philo[%d]->last eat = %li->time whitout eating = %li]\n",
				// 	data->dead_philo->id + 1, get_last_eat(philo), get_time(philo) - get_last_eat(philo));
				kill_all_philos(philo, &philo[i]);
				return ;
			}
			if (data->must_eat != -1 && check_eat(philo) == true)
			{
				end_philos(data, &philo[i]);
				return ;
			}
			// printf("[DEBUG: philo[%d]->last eat = %li->time whitout eating = %li]\n",
			// data->dead_philo->id + 1, get_last_eat(&philo[i]), get_time(philo) - get_last_eat(&philo[i]));
			pthread_mutex_unlock(&philo[i].check_dead_mutex);
		}
	}
}

void	kill_all_philos(t_philo *philos, t_philo *dead_philo)
{
	int		i;
	int		philo_number;
	long	time;
	
	time = get_time(philos);
	pthread_mutex_lock(&philos->data->printf_mutex);
	philo_number = philos->data->philos_number;
	i = -1;
	while (++i < philo_number)
	{
		if (&philos[i] != dead_philo)
			pthread_mutex_lock(&philos[i].check_dead_mutex);
	}
	printf("%li	%d	died\n", time / 1000, dead_philo->id + 1);
	i = -1;
	while (++i < philo_number)
	{
		philos[i].dead = true;
	}
	i = -1;
	while (++i < philo_number)
		pthread_mutex_unlock(&philos[i].check_dead_mutex);
	pthread_mutex_unlock(&philos->data->printf_mutex);
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
