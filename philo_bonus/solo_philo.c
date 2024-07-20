/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:51:23 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/20 20:35:28 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_solo_philo(t_data *data)
{
	memset(&data->philo, 0, sizeof(t_philo));
	data->philo.id = 0;
	data->pid[0] = fork();
	if (data->pid[0] == -1)
		end_philos(data, 0);
	if (data->pid[0] == 0)
		solo_philo(data);
}

void	solo_philo(t_data *data)
{
	long	time;

	time = get_time(data);
	sem_wait(&data->forks);
	mutex_printf("has taken a fork", time, data);
	while (time < data->time_to_die)
	{
		time = get_time(data);
		usleep(100);
	}
	sem_post(&data->forks);
	mutex_printf("died", time, data);
	exit(EXIT_SUCCESS);
}
