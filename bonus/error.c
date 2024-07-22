/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:44:14 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/22 07:19:44 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int		ft_putendl_fd(const char *s, int fd);

int	error(char *err, int exit_status)
{
	if (err != NULL)
		printf("Error: %s\n", err);
	return (exit_status);
}

void	end_philos(t_data *data, int philos_number)
{
	static bool	first_call = true;
	int			i;

	if (first_call == false)
		return ;
	else
		first_call = false;
	i = 0;
	while (i < philos_number)
	{
		kill(data->pid[i], SIGKILL);
		++i;
	}
}

static void	destroy_semaphores(t_data *data)
{
	sem_close(data->dead_check);
	sem_unlink("dead_check");
	sem_close(data->eat_check);
	sem_unlink("eat_check");
	sem_close(data->forks);
	sem_unlink("forks");
	sem_close(data->kill_process);
	sem_unlink("kill_process");
	sem_close(data->printf_mutex);
	sem_unlink("printf_mutex");
	sem_close(data->taking_forks);
	sem_unlink("taking_forks");
	sem_close(data->last_eat_sem);
	sem_unlink("last_eat_sem");
}

void	free_and_exit(char *error, int status, t_data *data, bool errno)
{
	destroy_semaphores(data);
	if (error != NULL)
	{
		if (errno == true)
			perror(error);
		else
			ft_putendl_fd(error, STDERR_FILENO);
	}
	if (data->pid == NULL)
		kill_sig(data);
	else
		free(data->pid);
	exit (status);
}

void	exit_and_kill(char *err, int status, t_data *data)
{
	if (err != NULL)
		printf("Error: %s\n", err);
	kill_sig(data);
	exit(status);
}
