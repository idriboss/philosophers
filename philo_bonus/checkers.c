/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:59:33 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/20 20:46:59 by ibaby            ###   ########.fr       */
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
	printf("[1]\n");
	sem_wait(&data->dead_check);
	exit_and_kill(NULL, EXIT_SUCCESS, data);
}

void	eat_checker(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_number)
	{
		printf("[1]\n");
		sem_wait(&data->eat_check);
		++i;
	}
	exit_and_kill(NULL, EXIT_SUCCESS, data);
}
