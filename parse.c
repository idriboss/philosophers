/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:52:35 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/09 15:35:07 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse(char **argv, t_data *data)
{
	data->philos_number = ft_atol(argv[1]);
	if (data->philos_number < 1)
		return (error("Error: number of philosophers", EXIT_FAILURE));
	data->time_to_die = ft_atol(argv[2]);
	if (data->time_to_die == -1)
		return (error("Error: time to die", EXIT_FAILURE));
	data->time_to_eat = ft_atol(argv[3]);
	if (data->time_to_eat == -1)
		return (error("Error: time to eat", EXIT_FAILURE));
	data->time_to_sleep = ft_atol(argv[4]);
	if (data->time_to_sleep == -1)
		return (error("Error: time to sleep", EXIT_FAILURE));
	if (argv[5] != NULL)
	{
		data->must_eat = ft_atol(argv[5]);
		if (data->must_eat == -1)
			return (error("Error: number of times each philosopher must eat",
				EXIT_FAILURE));
	}
	else
		data->must_eat = -1;
	return (EXIT_SUCCESS);
}
