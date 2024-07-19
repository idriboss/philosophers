/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:06:48 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/19 23:37:32 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	dead_philo(t_data *data)
{
	long int	time_without_eat;
	sem_t		*dead_mutex;
	bool		*check_dead;

	check_dead = &data->philo.is_dead;
	time_without_eat = (get_time(data) - get_last_eat(data));
	if (*check_dead == true)
	{
		return (true);
	}
	if (time_without_eat >= data->time_to_die)
	{
		*check_dead = true;
		sem_post(data->);
		return (true);
	}
	return (false);
}

int	take_fork(t_philo *philo)
{
	if (philo->data->philos_number % 2 == 0)
	{
		sem_wait(&philo->fork);
		if (mutex_printf("has taken a fork", get_time(philo), philo) ==
			EXIT_FAILURE)
			return (sem_post(&philo->fork), EXIT_FAILURE);
		sem_wait(philo->next_fork);
		if (mutex_printf("has taken a fork", get_time(philo), philo) ==
			EXIT_FAILURE)
			return (drop_fork(philo), EXIT_FAILURE);
	}
	else
	{
		sem_wait(philo->next_fork);
		if (mutex_printf("has taken a fork", get_time(philo), philo) ==
			EXIT_FAILURE)
			return (sem_post(philo->next_fork), EXIT_FAILURE);
		sem_wait(&philo->fork);
		if (mutex_printf("has taken a fork", get_time(philo), philo) ==
			EXIT_FAILURE)
			return (drop_fork(philo), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	drop_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		sem_post(&philo->fork);
		sem_post(philo->next_fork);
	}
	else
	{
		sem_post(philo->next_fork);
		sem_post(&philo->fork);
	}
	return (EXIT_SUCCESS);
}

int	mutex_printf(char *str, long int time, t_philo *philo)
{
	sem_t	*printf_mutex;

	printf_mutex = &philo->data->printf_mutex;
	sem_wait(printf_mutex);
	if (check_philo(philo) == true)
		return (sem_post(printf_mutex), EXIT_FAILURE);
	printf("%li	%i	%s\n", time / 1000, philo->id + 1, str);
	sem_post(printf_mutex);
	return (EXIT_SUCCESS);
}
