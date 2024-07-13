/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:44:33 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/13 05:10:02 by ibaby            ###   ########.fr       */
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
