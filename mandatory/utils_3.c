/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:44:33 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/13 11:58:37 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->check_dead_mutex);
	philo->dead = true;
	pthread_mutex_unlock(&philo->check_dead_mutex);
}

bool	get_dead(t_philo *philo)
{
	bool	check_dead;

	pthread_mutex_lock(&philo->check_dead_mutex);
	check_dead = philo->dead;
	pthread_mutex_unlock(&philo->check_dead_mutex);
	return (check_dead);
}
void	set_dead_philo(t_philo *philo)
{
	static int	number_of_calls = 0;

	if (number_of_calls != 0)
		return ;
	number_of_calls = 1;
	pthread_mutex_lock(&philo->data->dead_philo_mutex);
	philo->data->dead_philo = philo;
	pthread_mutex_unlock(&philo->data->dead_philo_mutex);
}

t_philo	*get_dead_philo(t_philo *philo)
{
	t_philo	*dead_philo;

	pthread_mutex_lock(&philo->data->dead_philo_mutex);
	dead_philo = philo->data->dead_philo;
	pthread_mutex_unlock(&philo->data->dead_philo_mutex);
	return (dead_philo);
}

void	start_solo_philo(t_data *data)
{
	pthread_create(&data->philos->thread, NULL, solo_philo, data);
	pthread_join(data->philos->thread, )
}
