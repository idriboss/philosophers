/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:54:37 by ibaby             #+#    #+#             */
/*   Updated: 2024/07/10 15:25:12 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philos(t_data *data);
t_philo	*create_philo(int id, t_philo *before);

int	init_data(t_data *data)
{
	pthread_mutex_t	*printf_mutex;

	printf_mutex = malloc(sizeof(pthread_mutex_t) * 1);
	if (printf_mutex == NULL)
		return (EXIT_FAILURE);
	data->printf_mutex = printf_mutex;
	data->first_philo = init_philos(data);
	if (data->first_philo == NULL)
		return (free(printf_mutex), EXIT_FAILURE);
	if (pthread_mutex_init(printf_mutex, NULL) != EXIT_SUCCESS)
		return (free(printf_mutex), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_philo	*init_philos(t_data *data)
{
	t_philo	*first;
	t_philo	*temp;
	int		i;

	first = create_philo(0, NULL);
	if (first == NULL)
		return (NULL);
	first->data = data;
	temp = first;
	i = 0;
	while (++i < data->philos_number)
	{
		temp->next = create_philo(i, temp);
		if (temp == NULL)
		{
			ft_lstclear(&first);
			return (NULL);
		}
		temp->next->data = data;
		temp->next->before_fork = temp->fork;
		temp = temp->next;
	}
	temp->next = first;
	first->before_fork = temp->fork;
	return (first);
}

t_philo	*create_philo(int id, t_philo *before)
{
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_t		*thread;

	philo = malloc(sizeof(t_philo) * 1);
	if (philo == NULL)
		return (fprintf(stderr, "%s\n", MALLOC_FAILED), NULL);
	memset(philo, 0, sizeof(t_philo));
	fork = malloc(sizeof(pthread_mutex_t) * 1);
	if (fork == NULL)
		return (free(philo), fprintf(stderr, "%s\n", MALLOC_FAILED), NULL);
	thread = malloc(sizeof(pthread_t) * 1);
	if (thread == NULL)
		return (free(fork), free(philo), fprintf(stderr, "%s\n", MALLOC_FAILED),
			NULL);
	if (pthread_mutex_init(fork, NULL) != EXIT_SUCCESS)
		return (free(fork), free(philo), free(thread), NULL);
	philo->fork = fork;
	philo->thread = thread;
	philo->id = id;
	if (before != NULL)
		philo->before_fork = before->fork;
	return (philo);
}
