/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:54:59 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/12 02:58:08 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define MALLOC_FAILED "syscall: malloc failed"

typedef struct s_data
{
	long int		start_time;
	struct s_philo	*philos;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	check_dead_mutex;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				philos_number;
	int				must_eat;
	int				dead_status;
	bool			check_dead;
	bool			check_eat;
}					t_data;

typedef struct s_philo
{
	long int		last_eat;
	pthread_t		thread;
	pthread_mutex_t	fork;
	t_data			*data;
	pthread_mutex_t	*next_fork;
	int				id;
	bool			dead;
}					t_philo;

typedef struct s_routine_arg
{
	t_data			*data;
	t_philo			*philo;
	int				id;
}					t_routine_arg;

long int			ft_atol(const char *str);
void				print_err_and_exit(char *err, int exit_status);
int					error(char *err, int exit_status);
int					init_data(t_data *data);
int					parse(char **argv, t_data *data);
void				ft_lstclear(t_philo **lst);
int					ft_usleep(long int time, t_philo *philo);
long int			get_time(t_philo *philo);
t_philo				*routine(void *philo);
int					take_fork(t_philo *philo);
int					drop_fork(t_philo *philo);
void				kill_all_philos(t_philo *philo);
int					ft_die(t_philo *philo);
bool				get_dead(t_philo *philo);
void				set_dead(t_philo *philo);
void				mutex_printf(char *str, long int time, t_philo *philo);
bool				dead_check(t_philo *philo);

#endif