/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:54:37 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/16 21:44:40 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_data *data)
{
	int		i;
	int		len;
	t_philo	*philos;

	i = -1;
	len = data->philos_number;
	philos = malloc(sizeof(t_philo) * len);
	if (philos == NULL)
		return (EXIT_FAILURE);
	while (++i < len)
	{
		memset(&philos[i], 0, sizeof(t_philo));
		philos[i].id = i;
		philos[i].data = data;
		pthread_mutex_init(&philos[i].fork, NULL);
		pthread_mutex_init(&philos[i].check_dead_mutex, NULL);
		pthread_mutex_init(&philos[i].eat_count_mutex, NULL);
		pthread_mutex_init(&philos[i].last_eat_mutex, NULL);
		if (i + 1 != len)
			philos[i].next_fork = &philos[i + 1].fork;
		else
			philos[i].next_fork = &philos[0].fork;
	}
	data->philos = philos;
	return (EXIT_SUCCESS);
}

int	init_data(t_data *data)
{
	if (pthread_mutex_init(&data->printf_mutex, NULL) != EXIT_SUCCESS)
		return (pthread_mutex_destroy(&data->printf_mutex), EXIT_FAILURE);
	if (pthread_mutex_init(&data->dead_philo_mutex, NULL) != EXIT_SUCCESS)
		return (pthread_mutex_destroy(&data->printf_mutex), EXIT_FAILURE);
	if (init_philos(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
