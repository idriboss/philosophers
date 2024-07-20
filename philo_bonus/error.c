/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:44:14 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/20 20:35:09 by ibaby            ###   ########.fr       */
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
	int	i;

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

void	exit_and_kill(char *err, int status, t_data *data)
{
	if (err != NULL)
		printf("Error: %s\n", err);
	sem_post(&data->kill_process);
	exit(status);
}
