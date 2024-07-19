/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:44:42 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/19 23:43:59 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int		start_process(t_data *data);
int		wait_process(t_data *data);
bool	check_philos(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc != 5 && argc != 6)
		exit(EXIT_FAILURE);
	if (parse(argv, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_data(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (data.philos_number == 1)
		start_solo_philo(&data);
	else if (start_process(&data) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	start_process(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	sem_wait(&data->printf_mutex);
	while (i < data->philos_number)
	{
		memset(&data->philo, 0, sizeof(t_philo));
		data->philo.id = i;
		data->pid[i] = fork();
		if (data->pid[i] == 0)
		{
			return (routine(data));
		}
		++i;
	}
	start_checkers(data);
	sem_post(&data->printf_mutex);
	check_philos(data);
	if (wait_process(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

bool	check_philos(t_data *data)
{
	int	i;

	i = 0;
	sem_wait(&data->dead_mutex);
	sem_wait(&data->printf_mutex);
	while (i < data->philos_number)
	{
		kill(data->pid[i], SIGKILL);
		++i;
	}
	sem_post(&data->printf_mutex);
	sem_post(&data->dead_mutex);
}

int	wait_process(t_data *data)
{
	int		i;
	int		status;
	int		temp_status;

	i = 0;
	status = EXIT_SUCCESS;
	while (i < data->philos_number)
	{
		waitpid(data->pid[i], &temp_status, 0);
		if (WEXITSTATUS(temp_status) != EXIT_SUCCESS)
			status = EXIT_FAILURE;
		++i;
	}
	return (status);
}

void	
