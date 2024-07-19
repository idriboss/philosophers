/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:22:55 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/19 22:25:55 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_think(t_data *data);
static void	ft_sleep(t_data *data);
static void	ft_eat(t_data *data);

void	routine(t_data *data)
{
	sem_wait(&data->printf_mutex);
	sem_post(&data->printf_mutex);
	while (1)
	{
		ft_think(data);
		ft_eat(data);
		ft_sleep(data);
	}
}

static int	ft_think(t_data *data)
{
	long int	time;

	time = get_time(data);
	if (mutex_printf("is thinking", time, data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_sleep(t_data *data)
{
	long int	time;

	time = get_time(philo);
	if (mutex_printf("is sleeping", time, philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_usleep(philo->data->time_to_sleep, philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ft_eat(t_data *data)
{
	t_data		*data;
	long int	time;
	long int	time_to_eat;

	data = philo->data;
	time_to_eat = data->time_to_eat;
	if (data->must_eat != -1 && philo->eat_count >= data->must_eat)
		return (EXIT_FAILURE);
	if (take_fork(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	time = get_time(philo);
	set_last_eat(philo, time);
	if (mutex_printf("is eating", time, philo) == EXIT_FAILURE)
		return (drop_fork(philo), EXIT_FAILURE);
	increase_eat_count(philo);
	if (ft_usleep(time_to_eat, philo) == EXIT_FAILURE)
		return (drop_fork(philo), EXIT_FAILURE);
	drop_fork(philo);
	return (EXIT_SUCCESS);
}

void	*solo_philo(void *data_arg)
{
	t_data	*data;
	t_philo	*philo;
	long	time;

	data = (t_data *)data_arg;
	philo = data->philos;
	data->start_time = get_time(philo);
	time = get_time(philo);
	sem_wait(&philo->fork);
	mutex_printf("has taken a fork", time, philo);
	while (time < data->time_to_die)
	{
		time = get_time(philo);
		usleep(100);
	}
	sem_post(&philo->fork);
	mutex_printf("died", time, philo);
	return (NULL);
}
