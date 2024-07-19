/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:54:59 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/19 23:43:12 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <semaphore.h>
# include <unistd.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# define MALLOC_FAILED "syscall: malloc failed"

typedef struct s_data
{
	sem_t			forks;
	sem_t			dead_mutex;
	sem_t			printf_mutex;
	sem_t			dead_check;
	sem_t			eat_check;
	struct s_philo	philo;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				*pid;
	int				philos_number;
	int				must_eat;
}					t_data;

typedef struct s_philo
{
	unsigned long	last_eat;
	int				eat_count;
	int				id;
	bool			is_dead;
}					t_philo;

long int			ft_atol(const char *str);
void				print_err_and_exit(char *err, int exit_status);
int					error(char *err, int exit_status);
int					init_data(t_data *data);
int					parse(char **argv, t_data *data);
void				ft_lstclear(t_philo **lst);
int					ft_usleep(long int time, t_philo *philo);
long long int		get_time(t_philo *philo);
t_philo				*routine(void *philo);
int					take_fork(t_philo *philo);
int					drop_fork(t_philo *philo);
int					ft_die(t_philo *philo);
bool				get_dead(t_philo *philo);
void				set_dead(t_philo *philo);
int					mutex_printf(char *str, long long time, t_philo *philo);
bool				dead_check(t_philo *philo);
void				set_dead_philo(t_philo *philo);
t_philo				*get_dead_philo(t_philo *philo);
void				start_solo_philo(t_data *data);
void				*solo_philo(void *data_arg);
bool				check_eat(t_philo *philo);
void				end_philos(t_data *data, t_philo *locked_philo);

#endif