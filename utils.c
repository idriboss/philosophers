#include "philo.h"

long int	ft_atol(const char *str, t_data *data)
{
	int		i;
	int		sign;
	long	number;

	i = 0;
	sign = 1;
	number = 0;
	
	if (str[i] < '0' && str[i] > '9')
		free_and_exit("Error: bad inputs", EXIT_FAILURE, data);
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' && str[i] < '0' && str[i] > '9')
		free_and_exit("Error: bad inputs", EXIT_FAILURE, data);
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

int	ft_sleep(long long int milliseconds)
{
	struct timeval	start;
	long long int	current;

	if (gettimeofday(&start, NULL) == -1)
		return (0);
	current = get_time();
	if (current == 0)
		return (EXIT_FAILURE);
	while (current - (long long)(start.tv_sec * 1000000 +
		start.tv_usec) < milliseconds * 1000)
	{
		if (usleep(10) == -1)
			return (EXIT_FAILURE);
	}
	
}

long long int	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (EXIT_FAILURE);
	return (time.tv_sec * 1000000 + time.tv_usec);
}
