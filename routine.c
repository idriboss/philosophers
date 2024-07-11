/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:22:55 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/11 23:42:57 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static int	ft_think(t_philo *philo);
// static int	ft_sleep(t_philo *philo);
static int	ft_eat(t_philo *philo);

t_philo	*routine(void *philosopher)
{
	t_philo	*philo;
	long int	time;
	philo = (t_philo *)philosopher;
	time = get_time(philo->data);
	philo->last_eat = time;
	if ((philo->id + 1) % 2 != 0)
		usleep(20);
	// printf("philo[%d]->dead: %d\n", philo->id, philo->dead);
	while (philo->dead != true)
	{
		printf("Entered Id[%d]\n", philo->id);
		if (ft_eat(philo) == EXIT_FAILURE)
			return (philo);
	}
	return (philo);
}
/*
static int	ft_think(t_philo *philo)
{
	long int	time;

	time = get_time(philo->data);
	if (philo->dead == true)
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(philo->data->printf_mutex) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (philo->dead == true)
	{
		pthread_mutex_unlock(philo->data->printf_mutex);
		return (EXIT_FAILURE);
	}
	if (printf("%li	%d is thinking\n", time, philo->id + 1)
		== -1)
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(philo->data->printf_mutex) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_sleep(t_philo *philo)
{
	long int	time;

	time = get_time(philo->data);
	if (philo->dead == true)
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(philo->data->printf_mutex) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (philo->dead == true)
	{
		pthread_mutex_unlock(philo->data->printf_mutex);
		return (EXIT_FAILURE);
	}
	if (printf("%li	%d is sleeping\n", time, philo->id + 1)
		== -1)
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(philo->data->printf_mutex) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (usleep(philo->data->time_to_sleep) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
*/
static int	ft_eat(t_philo *philo)
{
	long int	time;

	if (take_fork(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	time = get_time(philo->data);
	philo->last_eat = time;
	pthread_mutex_lock(&philo->data->printf_mutex);
	printf("%li	%d is eating\n", time, philo->id + 1);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	usleep(philo->data->time_to_eat);
	drop_fork(philo);
	return (EXIT_SUCCESS);
}

/*int	ft_die(t_philo *philo)
{
	long int	time;

	time = get_time(philo->data);
	if (pthread_mutex_lock(philo->data->printf_mutex) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	printf("die\n");
	if (philo->dead == true)
	{
		pthread_mutex_unlock(philo->data->printf_mutex);
		return (EXIT_FAILURE);
	}
	if (printf("%li	%d died\n", time, philo->id + 1)
		== -1)
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(philo->data->printf_mutex) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	kill_all_philos(philo);
	return (EXIT_SUCCESS);
}*/
