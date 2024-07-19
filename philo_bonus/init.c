/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:54:37 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/19 21:23:50 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_data(t_data *data)
{
	int	philo_num;

	philo_num = data->philos_number;
	data->pid = malloc(sizeof(int) * philo_num);
	if (data->pid == NULL)
		return (EXIT_FAILURE);
	if (sem_init(&data->printf_mutex, philo_num, 1) != EXIT_SUCCESS)
		return (pthread_mutex_destroy(&data->printf_mutex), EXIT_FAILURE);
	if (sem_init(&data->forks, philo_num, 1) != EXIT_SUCCESS)
		return (pthread_mutex_destroy(&data->printf_mutex), EXIT_FAILURE);
	if (sem_init(&data->dead_mutex, philo_num, 1) != EXIT_SUCCESS)
		return (pthread_mutex_destroy(&data->printf_mutex), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
