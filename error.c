#include "philo.h"

int		ft_putendl_fd(const char *s, int fd);

void	print_err_and_exit(char *err, int exit_status)
{
	if (err != NULL)
		ft_putendl_fd(err, STDERR_FILENO);
	exit(exit_status);
}

int	error(char *err, int exit_status)
{
	if (err != NULL)
	{
		if (printf("%s\n", err) == -1)
			return (EXIT_FAILURE);
	}
	return (exit_status);
}
