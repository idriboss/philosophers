/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:54:59 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/08 23:33:01 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data
{
	long int		start_time;
	struct s_philo	*first_philo;
	pthread_mutex_t	*printf_mutex;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				philos_number;
	int				must_eat;
	int				dead_status;
	bool			check_dead;
	bool			check_eat;
}	t_data;

typedef struct s_philo
{
	long int		last_eat;
	pthread_t		*thread;
	pthread_mutex_t	*fork_mutex;
	t_data			*data;
	struct s_philo	*before;
	struct s_philo	*next;
	int				id;
	bool			dead;
}	t_philo;

typedef struct s_routine_arg
{
	t_data	*data;
	t_philo	*philo;
	int		id;
}	t_routine_arg;

long int		ft_atol(const char *str, t_data *data);
void			print_err_and_exit(char *err, int exit_status);
void			free_and_exit(char *err, int exit_status, t_data *data);
void			init_data(t_data *data);
void			parse(char **argv, t_data *data);
void			ft_lstclear(t_philo **lst);
int				ft_usleep(long int milliseconds, t_philo *philo);
long int	get_time(t_data *data);
int				*routine(t_philo *philo);
int				take_fork(t_philo *philo, pthread_mutex_t *fork);
int				drop_fork(t_philo *philo, pthread_mutex_t *fork);
void			kill_all_philos(t_philo *philo);
int				ft_die(t_philo *philo);

#endif