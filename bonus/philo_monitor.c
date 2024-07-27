/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 07:11:46 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/27 19:56:59 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_philo_monitor(t_data *data)
{
	pthread_create(data->monitor, 0, (void *)philo_monitoring, (void *)data);
	pthread_detach(*data->monitor);
}

void	philo_monitoring(void *data_param)
{
	t_data		*data;

	data = (t_data *)data_param;
	while (1)
	{
		if (dead_philo(data) == true)
			exit(EXIT_SUCCESS);
		usleep(100);
	}
}

long long	get_last_eat(t_data *data)
{
	long long	last_eat;

	sem_wait(data->last_eat_sem);
	last_eat = data->last_eat;
	sem_post(data->last_eat_sem);
	return (last_eat);
}

void	set_last_eat(long long time, t_data *data)
{
	sem_wait(data->last_eat_sem);
	data->last_eat = time;
	sem_post(data->last_eat_sem);
}
