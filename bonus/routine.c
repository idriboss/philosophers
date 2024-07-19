/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:22:55 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/17 20:54:05 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_think(t_philo *philo);
static int	ft_sleep(t_philo *philo);
static int	ft_eat(t_philo *philo);

t_philo	*routine(void *philosopher)
{
	t_philo		*philo;

	philo = (t_philo *)philosopher;
	pthread_mutex_lock(&philo->data->printf_mutex);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	if (philo->id % 2 == 1)
		usleep(500);
	while (philo->data->check_dead != true)
	{
		if (ft_think(philo) == EXIT_FAILURE)
			return (NULL);
		if (ft_eat(philo) == EXIT_FAILURE)
			return (NULL);
		if (ft_sleep(philo) == EXIT_FAILURE)
			return (NULL);
	}
	return (NULL);
}

static int	ft_think(t_philo *philo)
{
	long int	time;

	time = get_time(philo);
	if (mutex_printf("is thinking", time, philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_sleep(t_philo *philo)
{
	long int	time;

	time = get_time(philo);
	if (mutex_printf("is sleeping", time, philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_usleep(philo->data->time_to_sleep, philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_eat(t_philo *philo)
{
	t_data		*data;
	long int	time;
	long int	time_to_eat;

	data = philo->data;
	time_to_eat = data->time_to_eat;
	if (data->must_eat != -1 && philo->eat_count >= data->must_eat)
		return (EXIT_FAILURE);
	if (take_fork(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	time = get_time(philo);
	set_last_eat(philo, time);
	if (mutex_printf("is eating", time, philo) == EXIT_FAILURE)
		return (drop_fork(philo), EXIT_FAILURE);
	increase_eat_count(philo);
	if (ft_usleep(time_to_eat, philo) == EXIT_FAILURE)
		return (drop_fork(philo), EXIT_FAILURE);
	drop_fork(philo);
	return (EXIT_SUCCESS);
}

void	*solo_philo(void *data_arg)
{
	t_data	*data;
	t_philo	*philo;
	long	time;

	data = (t_data *)data_arg;
	philo = data->philos;
	data->start_time = get_time(philo);
	time = get_time(philo);
	pthread_mutex_lock(&philo->fork);
	mutex_printf("has taken a fork", time, philo);
	while (time < data->time_to_die)
	{
		time = get_time(philo);
		usleep(100);
	}
	pthread_mutex_unlock(&philo->fork);
	mutex_printf("died", time, philo);
	return (NULL);
}
