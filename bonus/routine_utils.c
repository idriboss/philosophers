/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 22:06:48 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/22 07:49:49 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	dead_philo(t_data *data)
{
	long long	time;

	time = get_time(data);
	if ((time - get_last_eat(data)) >= data->time_to_die)
	{
		sem_wait(data->printf_mutex);
		printf("%lli	%i	died\n",
			(time - data->start_time) / 1000, data->philo.id + 1);
		kill_sig(data);
		return (true);
	}
	return (false);
}

int	take_fork(t_data *data)
{
	sem_wait(data->taking_forks);
	sem_wait(data->forks);
	if (mutex_printf("has taken a fork", get_time(data), data)
		== EXIT_FAILURE)
		return (drop_fork(data, 1), EXIT_FAILURE);
	sem_wait(data->forks);
	if (mutex_printf("has taken a fork", get_time(data), data)
		== EXIT_FAILURE)
		return (drop_fork(data, 2), EXIT_FAILURE);
	sem_post(data->taking_forks);
	return (EXIT_SUCCESS);
}

int	drop_fork(t_data *data, int forks)
{	
	while (forks > 0)
	{
		if (sem_post(data->forks) != EXIT_SUCCESS)
			exit_and_kill("function drop_fork failed", EXIT_FAILURE, data);
		--forks;
	}
	return (EXIT_SUCCESS);
}

void	check_eat(t_data *data)
{
	static int	eat_count = 0;

	if (++eat_count > data->must_eat)
		return ;
	if (eat_count == data->must_eat)
		sem_post(data->eat_check);
}

// void	set_last_eat(t_data *data, long long time)
// {
// }
