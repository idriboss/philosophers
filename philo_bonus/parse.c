/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:52:35 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/21 20:19:40 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	parse(char **argv, t_data *data)
{
	data->philos_number = ft_atol(argv[1]);
	if (data->philos_number < 1)
		return (error("Error: number of philosophers", EXIT_FAILURE));
	data->time_to_die = ft_atol(argv[2]) * 1000;
	if (data->time_to_die < 0)
		return (error("time to die", EXIT_FAILURE));
	data->time_to_eat = ft_atol(argv[3]) * 1000;
	if (data->time_to_eat < 0)
		return (error("time to eat", EXIT_FAILURE));
	data->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (data->time_to_sleep < 0)
		return (error("time to sleep", EXIT_FAILURE));
	if (argv[5] != NULL)
	{
		data->must_eat = ft_atol(argv[5]);
		if (data->must_eat < 0)
			return (error("Error: number of times each philosopher must eat",
					EXIT_FAILURE));
	}
	else
		data->must_eat = -1;
	return (EXIT_SUCCESS);
}
