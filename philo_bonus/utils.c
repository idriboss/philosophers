/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:44:27 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/20 20:31:04 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long int	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	number;

	i = 0;
	number = 0;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] < '0' && str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (number * sign);
}

int	ft_putstr_fd(const char *s, int fd)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
	{
		if (write(fd, &s[i], 1) < 0)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_putendl_fd(const char *s, int fd)
{
	int	check;

	if (!s)
		return (0);
	check = ft_putstr_fd(s, fd);
	if (check < 0)
		return (-1);
	if (write(fd, "\n", 1) < 0)
		return (-1);
	check++;
	return (check);
}

int	ft_usleep(long int microseconds, t_data *data)
{
	long int	start;
	long int	temp;

	temp = 0;
	start = get_time(data);
	if (start == -1)
		return (EXIT_FAILURE);
	while ((temp - start) < microseconds)
	{
		temp = get_time(data);
		usleep(100);
	}
	return (EXIT_SUCCESS);
}

long long int	get_time(t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		exit_and_kill("gettimeofday function failed", EXIT_FAILURE, data);
	return (time.tv_sec * 1000000 + time.tv_usec);
}
