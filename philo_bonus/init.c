/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:54:37 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/20 20:54:51 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_data(t_data *data)
{
	int	philo_num;

	philo_num = data->philos_number;
	data->pid = malloc(sizeof(int) * (philo_num + 2));
	if (data->pid == NULL)
		exit(error(MALLOC_FAILED, EXIT_FAILURE));
	if (sem_init(&data->forks, philo_num, philo_num) != EXIT_SUCCESS)
		return (sem_destroy(&data->forks), EXIT_FAILURE);
	if (sem_init(&data->taking_forks, philo_num, 1) != EXIT_SUCCESS)
		return (sem_destroy(&data->taking_forks), EXIT_FAILURE);
	if (sem_init(&data->printf_mutex, philo_num, 1) != EXIT_SUCCESS)
		return (sem_destroy(&data->printf_mutex), EXIT_FAILURE);
	if (sem_init(&data->dead_check, philo_num, 0) != EXIT_SUCCESS)
		return (sem_destroy(&data->dead_check), EXIT_FAILURE);
	if (sem_init(&data->eat_check, philo_num, 0) != EXIT_SUCCESS)
		return (sem_destroy(&data->eat_check), EXIT_FAILURE);
	data->printf_mutex_p = &data->printf_mutex;
	return (EXIT_SUCCESS);
}
