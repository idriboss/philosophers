#include "philo.h"

int		ft_putendl_fd(const char *s, int fd);

void	print_err_and_exit(char *err, int exit_status)
{
	if (err != NULL)
		ft_putendl_fd(err, STDERR_FILENO);
	exit(exit_status);
}

void	free_and_exit(char *err, int exit_status, t_data *data)
{
	free(data);
	print_err_and_exit(err, exit_status);
}
