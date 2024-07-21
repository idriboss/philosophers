/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:22:55 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/21 17:49:14 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_think(t_data *data);
static void	ft_sleep(t_data *data);
static void	ft_eat(t_data *data);

void	routine(t_data *data)
{
	data->philo.last_eat = get_time(data);
	sem_wait(data->printf_mutex);
	sem_post(data->printf_mutex);
	data->start_time = get_time(data);
	while (1)
	{
		ft_think(data);
		ft_eat(data);
		ft_sleep(data);
	}
}

static void	ft_think(t_data *data)
{
	mutex_printf("is thinking", get_time(data), data);
}

static void	ft_sleep(t_data *data)
{
	mutex_printf("is sleeping", get_time(data), data);
	ft_usleep(data->time_to_sleep, data);
}

static void	ft_eat(t_data *data)
{
	long long	time;
	
	take_fork(data);
	time = get_time(data);
	check_eat(data);
	data->philo.last_eat = time;
	mutex_printf("is eating", time, data);
	ft_usleep(data->time_to_eat, data);
	drop_fork(data, 2);
}

int	mutex_printf(char *str, long long time, t_data *data)
{
	sem_t	*printf_mutex;

	printf_mutex = data->printf_mutex;
	sem_wait(printf_mutex);
	if (dead_philo(data) == true)
		exit_and_kill(NULL, EXIT_SUCCESS, data);
	if (printf("%lli	%i	%s\n", (time - data->start_time) / 1000,
		data->philo.id + 1, str) == -1)
	{
		sem_post(data->dead_check);
		exit_and_kill("printf function failed", EXIT_FAILURE, data);
	}
	sem_post(printf_mutex);
	return (EXIT_SUCCESS);
}
