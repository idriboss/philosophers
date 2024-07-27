/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:51:23 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/22 07:50:27 by ibaby            ###   ########.fr       */
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
	{
		data->pid = NULL;
		solo_philo(data);
	}
	sem_wait(data->kill_process);
}

void	solo_philo(t_data *data)
{
	long long	time;

	time = get_time(data);
	data->start_time = time;
	sem_wait(data->forks);
	printf("%lli	%i	is thinking\n",
		(time - data->start_time) / 1000, data->philo.id + 1);
	printf("%lli	%i	has taken a fork\n",
		(time - data->start_time) / 1000, data->philo.id + 1);
	while (time - data->start_time < data->time_to_die)
	{
		time = get_time(data);
		usleep(100);
	}
	sem_post(data->forks);
	printf("%lli	%i	died\n",
		(time - data->start_time) / 1000, data->philo.id + 1);
	kill_sig(data);
	exit(EXIT_SUCCESS);
}
