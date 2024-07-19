/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:44:14 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/17 20:25:21 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_putendl_fd(const char *s, int fd);

void	print_err_and_exit(char *err, int exit_status)
{
	if (err != NULL)
		ft_putendl_fd(err, STDERR_FILENO);
	exit(exit_status);
}

int	error(char *err, int exit_status)
{
	if (err != NULL)
	{
		if (printf("%s\n", err) == -1)
			return (EXIT_FAILURE);
	}
	return (exit_status);
}

void	end_philos(t_data *data, t_philo *locked_philo)
{
	t_philo	*philos;
	int		i;

	i = -1;
	philos = data->philos;
	while (++i < data->philos_number)
	{
		if (&philos[i] != locked_philo)
			pthread_mutex_lock(&philos[i].check_dead_mutex);
	}
	i = -1;
	while (++i < data->philos_number)
	{
		philos[i].dead = true;
	}
	i = -1;
	while (++i < data->philos_number)
	{
		pthread_mutex_unlock(&philos[i].check_dead_mutex);
	}
}
