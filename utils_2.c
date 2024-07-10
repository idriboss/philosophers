/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:06:48 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/10 22:17:18 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_lstclear(t_philo **lst)
{
	t_philo	*elm;
	t_philo	*tmp;

	elm = *lst;
	while (elm)
	{
		tmp = elm->next;
		pthread_mutex_destroy(elm->fork);
		free(elm->fork);
		free(elm);
		elm = tmp;
	}
}

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

int	take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	if (philo->dead == true)
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(fork) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (philo->dead == true)
		return (EXIT_FAILURE);
	if (pthread_mutex_lock(philo->data->printf_mutex) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (philo->dead == true)
		return (EXIT_FAILURE);
	if (printf("[%li]	%d  has taken a fork\n", get_time(philo->data),
				philo->id + 1) == -1)
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(philo->data->printf_mutex) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (philo->dead == true)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	drop_fork(t_philo *philo, pthread_mutex_t *fork)
{
	if (philo->dead == true)
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(fork) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
