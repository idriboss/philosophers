/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:54:59 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/02 19:02:26 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include "utils/utils.h"

typedef struct t_philo
{
	
}	t_philo;

typedef struct t_data
{
	t_philo	*philos;
}	t_data;

void	print_err_and_exit(char *err, int exit_status);
void	free_and_exit(char *err, int exit_status, t_data *data);

#endif