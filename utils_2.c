/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:06:48 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/11 21:16:14 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
void	kill_all_philos(t_philo *philo)
{
	t_philo	*first;

	first = philo;
	philo->dead = true;
	philo = philo->next;
	while (philo != first)
	{
		philo->dead = true;
		philo = philo->next;
	}
}
*/
int	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(&philo->fork) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		if (pthread_mutex_lock(&philo->data->printf_mutex) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		///verifier la mort
		printf("%li	%d  has taken a fork\n", get_time(philo->data), philo->id
					+ 1);
		if (pthread_mutex_unlock(&philo->data->printf_mutex) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		if (pthread_mutex_lock(philo->next_fork) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		if (pthread_mutex_lock(&philo->data->printf_mutex) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		///verifier la mort
		printf("%li	%d  has taken a fork\n", get_time(philo->data), philo->id
					+ 1);
		if (pthread_mutex_unlock(&philo->data->printf_mutex) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	else
	{
		if (pthread_mutex_lock(philo->next_fork) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		if (pthread_mutex_lock(&philo->data->printf_mutex) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		///verifier la mort
		printf("%li	%d  has taken a fork\n", get_time(philo->data), philo->id
					+ 1);
		if (pthread_mutex_unlock(&philo->data->printf_mutex) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		if (pthread_mutex_lock(&philo->fork) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		if (pthread_mutex_lock(&philo->data->printf_mutex) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		///verifier la mort
		printf("%li	%d  has taken a fork\n", get_time(philo->data), philo->id
					+ 1);
		if (pthread_mutex_unlock(&philo->data->printf_mutex) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->next_fork);
	return (EXIT_SUCCESS);
}
