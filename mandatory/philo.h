/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:54:59 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/16 23:06:38 by ibaby            ###   ########.fr       */
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
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	dead_philo_mutex;
	struct s_philo	*philos;
	struct s_philo	*dead_philo;
	long int		start_time;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				must_eat;
	int				philos_number;
	int				dead_status;
	bool			check_dead;
	bool			check_eat;
}					t_data;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	eat_count_mutex;
	pthread_mutex_t	check_dead_mutex;
	pthread_mutex_t	last_eat_mutex;
	pthread_mutex_t	*next_fork;
	t_data			*data;
	long int		last_eat;
	long int		next_sleep;
	int				eat_count;
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
int					ft_die(t_philo *philo);
bool				get_dead(t_philo *philo);
void				set_dead(t_philo *philo);
int					mutex_printf(char *str, long int time, t_philo *philo);
bool				dead_check(t_philo *philo);
void				set_dead_philo(t_philo *philo);
t_philo				*get_dead_philo(t_philo *philo);
void				start_solo_philo(t_data *data);
void				*solo_philo(void *data_arg);
bool				check_eat(t_philo *philo);
void				end_philos(t_data *data, t_philo *locked_philo);
void				increase_eat_count(t_philo *philo);
int					get_eat_count(t_philo *philo);
void				kill_all_philos(t_philo *philos, t_philo *dead_philo);
void				set_last_eat(t_philo *philo, long int time);
long				get_last_eat(t_philo *philo);

#endif