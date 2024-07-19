/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:43:30 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/19 21:54:02 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	check_eat(t_philo *philo)
{
	int	valid_philos;
	int	i;
	int	must_eat;
	int	philos_number;

	i = 0;
	valid_philos = 0;
	must_eat = philo->data->must_eat;
	philos_number = philo->data->philos_number;
	while (i < philos_number)
	{
		if (get_eat_count(&philo[i]) >= must_eat)
		{
			++valid_philos;
		}
		++i;
	}
	if (valid_philos == philos_number)
	{
		return (true);
	}
	return (false);
}

void	increase_eat_count(t_philo *philo)
{
	sem_wait(&philo->eat_count_mutex);
	philo->eat_count++;
	sem_post(&philo->eat_count_mutex);
}

int	get_eat_count(t_philo *philo)
{
	int	eat_count;

	sem_wait(&philo->eat_count_mutex);
	eat_count = philo->eat_count;
	sem_post(&philo->eat_count_mutex);
	return (eat_count);
}

long	get_last_eat(t_philo *philo)
{
	long	last_eat;

	sem_wait(&philo->last_eat_mutex);
	last_eat = philo->last_eat;
	sem_post(&philo->last_eat_mutex);
	return (last_eat);
}

void	set_last_eat(t_philo *philo, long int time)
{
	sem_wait(&philo->last_eat_mutex);
	philo->last_eat = time;
	sem_post(&philo->last_eat_mutex);
}
