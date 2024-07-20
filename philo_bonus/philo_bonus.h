/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:54:59 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/20 20:55:00 by ibaby            ###   ########.fr       */
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

typedef struct s_philo
{
	long long int	last_eat;
	int				eat_count;
	int				id;
	bool			is_dead;
}					t_philo;

typedef struct s_data
{
	sem_t			forks;
	sem_t			taking_forks;
	sem_t			printf_mutex;
	sem_t			*printf_mutex_p;
	sem_t			dead_check;
	sem_t			eat_check;
	sem_t			kill_process;
	struct s_philo	philo;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				*pid;
	int				philos_number;
	int				must_eat;
}					t_data;

long int			ft_atol(const char *str);
int					error(char *err, int exit_status);
int					init_data(t_data *data);
int					parse(char **argv, t_data *data);
int					ft_usleep(long int time, t_data *data);
long long int		get_time(t_data *data);
void				routine(t_data *data);
int					drop_fork(t_data * data, int forks);
int					mutex_printf(char *str, long long time, t_data *data);
void				start_solo_philo(t_data *data);
void				solo_philo(t_data *data);
void				check_eat(t_data *data);
void				eat_checker(t_data *data);
void				dead_checker(t_data *data);
void				end_philos(t_data *data, int philo_number);
void				start_checkers(t_data *data);
void				exit_and_kill(char *err_mssg, int status, t_data *data);
int					take_fork(t_data *data);
bool				dead_philo(t_data *data);
void				check_philos(t_data *data);
int					wait_process(t_data *data);
int					start_process(t_data *data);

#endif