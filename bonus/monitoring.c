/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:44:42 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/22 09:08:27 by ibaby            ###   ########.fr       */
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
	free_and_exit(NULL, EXIT_SUCCESS, &data, false);
}

int	start_process(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philos_number)
	{
		memset(&data->philo, 0, sizeof(t_philo));
		data->philo.id = i;
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			end_philos(data, i);
		if (data->pid[i] == 0)
		{
			free(data->pid);
			data->pid = NULL;
			routine(data);
			exit_and_kill("monitoring", EXIT_FAILURE, data);
		}
		++i;
	}
	start_checkers(data);
	check_philos(data);
	return (wait_process(data));
}

void	check_philos(t_data *data)
{
	sem_wait(data->kill_process);
	end_philos(data, data->philos_number + 2);
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

void	kill_sig(t_data *data)
{
	static bool	is_first_call = true;

	if (is_first_call == false)
		return ;
	is_first_call = false;
	sem_post(data->kill_process);
}
