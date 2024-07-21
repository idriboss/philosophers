/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:59:33 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/21 18:28:14 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	start_checkers(t_data *data)
{
	int	i;

	i = data->philos_number;
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		end_philos(data, i);
	if (data->pid[i++] == 0)
			dead_checker(data);
	data->pid[i] = fork();
	if (data->pid[i] == -1)
	{
		end_philos(data, i);
	}
	if (data->pid[i] == 0)
			eat_checker(data);
}

void	dead_checker(t_data *data)
{
	sem_wait(data->dead_check);
	sem_post(data->kill_process);
	exit(EXIT_SUCCESS);
}

void	eat_checker(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_number)
	{
		sem_wait(data->eat_check);
		++i;
	}
	sem_post(data->kill_process);
	exit(EXIT_SUCCESS);
}
