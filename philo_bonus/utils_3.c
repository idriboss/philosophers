/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:44:33 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/19 21:54:02 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_dead(t_philo *philo)
{
	sem_wait(&philo->check_dead_mutex);
	philo->dead = true;
	sem_post(&philo->check_dead_mutex);
}

bool	get_dead(t_philo *philo)
{
	bool	check_dead;

	sem_wait(&philo->check_dead_mutex);
	check_dead = philo->dead;
	sem_post(&philo->check_dead_mutex);
	return (check_dead);
}

void	set_dead_philo(t_philo *philo)
{
	static int	number_of_calls;

	number_of_calls = 0;
	if (number_of_calls != 0)
		return ;
	number_of_calls = 1;
	sem_wait(&philo->data->dead_philo_mutex);
	philo->data->dead_philo = philo;
	sem_post(&philo->data->dead_philo_mutex);
}

t_philo	*get_dead_philo(t_philo *philo)
{
	t_philo	*dead_philo;

	sem_wait(&philo->data->dead_philo_mutex);
	dead_philo = philo->data->dead_philo;
	sem_post(&philo->data->dead_philo_mutex);
	return (dead_philo);
}

void	start_solo_philo(t_data *data)
{
	pthread_create(&data->philos->thread, NULL, solo_philo, data);
	pthread_join(data->philos->thread, NULL);
}
