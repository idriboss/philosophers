/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:22:55 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/08 23:05:33 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_think(t_philo *philo);
int	ft_sleep(t_philo *philo);
int	ft_eat(t_philo *philo);

int	*routine(t_philo *philo)
{
	if (philo->id % 2 != 0)
		ft_sleep(20);
	while (philo->dead != true)
	{
		if (ft_think(philo) == EXIT_FAILURE)
			return (NULL);
		if (ft_eat(philo) == EXIT_FAILURE)
			return (NULL);
		if (ft_sleep(philo) == EXIT_FAILURE)
			return (NULL);
	}
	
}

static int	ft_think(t_philo *philo)
{
	if (philo->dead == true)
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(philo->data->printf_mutex) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (philo->dead == true)
	{
		pthread_mutex_unlock(philo->data->printf_mutex);
		return (EXIT_FAILURE);
	}
	if (printf("[%lli]	%d is thinking\n", get_time(philo->data), philo->id + 1)
		== -1)
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(philo->data->printf_mutex) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_sleep(t_philo *philo)
{
	if (philo->dead == true)
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(philo->data->printf_mutex) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (philo->dead == true)
	{
		pthread_mutex_unlock(philo->data->printf_mutex);
		return (EXIT_FAILURE);
	}
	if (printf("[%lli]	%d is sleeping\n", get_time(philo->data), philo->id + 1)
		== -1)
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(philo->data->printf_mutex) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (ft_usleep(philo->data->time_to_sleep) == EXIT_FAILURE)
		return (EXIT_FAILURE);
}

static int	ft_eat(t_philo *philo)
{
	if (take_fork(philo, philo->fork_mutex) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (take_fork(philo, philo->before->fork_mutex) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(philo->data->printf_mutex) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (philo->dead == true)
	{
		pthread_mutex_unlock(philo->data->printf_mutex);
		return (EXIT_FAILURE);
	}
	if (printf("[%lli]	%d is eating\n", get_time(philo->data), philo->id + 1)
		== -1)
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(philo->data->printf_mutex) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (ft_usleep(philo->data->time_to_eat) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (drop_fork(philo, philo->fork_mutex) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (drop_fork(philo, philo->before->fork_mutex) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_die(t_philo *philo)
{
	if (pthread_mutex_lock(philo->data->printf_mutex) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (philo->dead == true)
	{
		pthread_mutex_unlock(philo->data->printf_mutex);
		return (EXIT_FAILURE);
	}
	if (printf("[%lli]	%d died\n", get_time(philo->data), philo->id + 1)
		== -1)
		return (EXIT_FAILURE);
	kill_all_philos(philo);
	return (EXIT_SUCCESS);
}
