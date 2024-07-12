/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:22:55 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/12 17:46:00 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_think(t_philo *philo);
static int	ft_sleep(t_philo *philo);
static int	ft_eat(t_philo *philo);

t_philo	*routine(void *philosopher)
{
	t_philo		*philo;
	long int	time;

	philo = (t_philo *)philosopher;
	pthread_mutex_lock(&philo->data->printf_mutex);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	time = get_time(philo);
	if (philo->data->philos_number % 2 == 1)
		ft_usleep(50, philo);
	philo->last_eat = time;
	while (philo->data->check_dead != true)
	{
		if (ft_think(philo) == EXIT_FAILURE)
			return (philo);
		if (ft_eat(philo) == EXIT_FAILURE)
			return (philo);
		if (ft_sleep(philo) == EXIT_FAILURE)
			return (philo);
	}
	return (philo);
}

static int	ft_think(t_philo *philo)
{
	long int	time;

	time = get_time(philo);
	if (dead_check(philo) == true)
		return (EXIT_FAILURE);
	mutex_printf("is thinking", time, philo);
	return (EXIT_SUCCESS);
}

static int	ft_sleep(t_philo *philo)
{
	long int	time;

	time = get_time(philo);
	if (dead_check(philo) == true)
		return (EXIT_FAILURE);
	mutex_printf("is sleeping", time, philo);
	if (ft_usleep(philo->data->time_to_sleep, philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_eat(t_philo *philo)
{
	long int	time;

	if (take_fork(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	time = get_time(philo);
	philo->last_eat = time;
	if (dead_check(philo) == true)
		return (drop_fork(philo), EXIT_FAILURE);
	mutex_printf("is eating", time, philo);
	ft_usleep(philo->data->time_to_eat, philo);
	drop_fork(philo);
	return (EXIT_SUCCESS);
}
