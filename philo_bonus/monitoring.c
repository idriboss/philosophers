/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:44:42 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/21 20:59:47 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc != 5 && argc != 6)
		exit(error(USAGE, EXIT_FAILURE));
	if (parse(argv, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_data(&data);
	if (data.philos_number == 1)
		start_solo_philo(&data);
	else if (start_process(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	start_process(t_data *data)
{
	int		i;

	i = 0;
	sem_wait(data->printf_mutex);
	while (i < data->philos_number)
	{
		// printf("[DEBUG]\n");
		memset(&data->philo, 0, sizeof(t_philo));
		data->philo.id = i;
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			end_philos(data, i);
		if (data->pid[i] == 0)
		{
			init_philo(data);
			routine(data);
			exit_and_kill("monitoring", EXIT_FAILURE, data);
		}
		++i;
	}
	start_checkers(data);
	sem_post(data->printf_mutex);
	check_philos(data);
	return (wait_process(data));
}

void	check_philos(t_data *data)
{
	sem_wait(data->kill_process);
	end_philos(data, data->philos_number + 2);
	// sem_post(data->printf_mutex); ?
	// sem_post(data->kill_process); ?
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
