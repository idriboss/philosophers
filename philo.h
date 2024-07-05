/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:54:59 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/05 20:57:15 by ibaby            ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_t		*thread;
	pthread_mutex_t	*fork_mutex;
	t_data			*data;
	t_philo			*before;
	t_philo			*next;
	int				id;
	bool			dead;
}	t_philo;

typedef struct s_data
{
	t_philo			*first_philo;
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

typedef struct s_routine_arg
{
	t_data	*data;
	t_philo	*philo;
	int		id;
}	t_routine_arg;

void	print_err_and_exit(char *err, int exit_status);
void	free_and_exit(char *err, int exit_status, t_data *data);
void	init_data(t_data *data);
void	parse(char *argv, t_data *data);
void	ft_lstclear(t_philo **lst);

#endif