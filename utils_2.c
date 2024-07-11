/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:06:48 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/11 23:46:22 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	dead_check(t_philo *philo)
{
	long int	time_without_eat;
	
	if (get_dead(philo) == true)
		return (true);
	time_without_eat = get_time(philo->data) - philo->last_eat;
	if (time_without_eat >= philo->data->time_to_die)
	{
		set_dead(philo);
		return (true);
	}
	return (false);
}

int	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->fork);
		if (dead_check(philo) == true)
			return (pthread_mutex_unlock(&philo->fork), EXIT_FAILURE);
		mutex_printf("has taken a fork\n", get_time(philo->data), philo);
		pthread_mutex_lock(philo->next_fork);
		if (dead_check(philo) == true)
			return (drop_fork(philo), EXIT_FAILURE);
		mutex_printf("has taken a fork\n", get_time(philo->data), philo);
	}
	else
	{
		pthread_mutex_lock(philo->next_fork);
		if (dead_check(philo) == true)
			return (pthread_mutex_unlock(philo->next_fork), EXIT_FAILURE);
		mutex_printf("has taken a fork\n", get_time(philo->data), philo);
		if (dead_check(philo) == true)
			return (drop_fork(philo), EXIT_FAILURE);
		pthread_mutex_lock(&philo->fork);
		mutex_printf("has taken a fork\n", get_time(philo->data), philo);
	}
	return (EXIT_SUCCESS);
}

int	drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->next_fork);
	return (EXIT_SUCCESS);
}

int	mutex_printf(char *str, long int time, t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->printf_mutex) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	printf("%li	%i ", time, philo->id);
	printf("%s\n", str);
	if (pthread_mutex_unlock(&philo->data->printf_mutex) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
