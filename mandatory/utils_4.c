/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:43:30 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/16 16:13:22 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_mutex);
}

int	get_eat_count(t_philo *philo)
{
	int	eat_count;

	pthread_mutex_lock(&philo->eat_count_mutex);
	eat_count = philo->eat_count;
	pthread_mutex_unlock(&philo->eat_count_mutex);
	return (eat_count);
}