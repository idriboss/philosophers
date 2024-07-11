#include "philo.h"

long int	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	number;

	i = 0;
	sign = 1;
	number = 0;
	
	if (str[i] < '0' && str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' && str[i] < '0' && str[i] > '9')
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
/*
int	ft_usleep(long int milliseconds, t_philo *philo)
{
	struct timeval	start_time;
	long int	current;
	long int	start;

	if (gettimeofday(&start_time, NULL) == -1)
		return (EXIT_FAILURE);
	start = start_time.tv_sec * 1000000 + start_time.tv_usec;
	current = get_time(philo->data);
	if (current == -1)
		return (EXIT_FAILURE);
	while (current - start < milliseconds * 1000)
	{
		current = get_time(philo->data);
		if (current == -1)
			return (EXIT_FAILURE);
		if (current > philo->last_eat + philo->data->time_to_die)
		{
			ft_die(philo);
			return (EXIT_FAILURE);
		}
		if (usleep(100) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}*/

long int	get_time(t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec * 1000000 + time.tv_usec - data->start_time) / 1000);
}
