/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:19:04 by codespace         #+#    #+#             */
/*   Updated: 2023/04/22 12:15:40 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	makan(t_philo *philo, int thread_id)
{
	pthread_mutex_lock(&(philo->fork[thread_id]));
	message(get_time(), thread_id + 1, "has taken a fork", philo);
	pthread_mutex_lock(&(philo->fork[((thread_id + 1) % philo->num)]));
	message(get_time(), thread_id + 1, "has taken a fork", philo);
	message(get_time(), thread_id + 1, "is eating", philo);
	pthread_mutex_lock(&philo->eat_check);
	philo->last_eat[thread_id] = get_time();
	pthread_mutex_unlock(&philo->eat_check);
	usleep(1000 * philo->time_eat);
	pthread_mutex_unlock(&(philo->fork[thread_id]));
	pthread_mutex_unlock(&(philo->fork[((thread_id + 1) % philo->num)]));
}

void	tidur_fikir(t_philo *philo, int thread_id)
{
	message(get_time(), thread_id + 1, "is sleeping", philo);
	usleep(1000 * philo->time_sleep);
	message(get_time(), thread_id + 1, "is thinking", philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		thread_id;
	int		num_eat;

	philo = (t_philo *)arg;
	thread_id = philo->index;
	num_eat = 0;
	while (!return_dead(philo) && num_eat != -1)
	{
		pthread_mutex_lock(&philo->eat_check);
		if (philo->check_full >= 0 && num_eat == philo->must_eat)
		{
			++philo->check_full;
			num_eat = -1;
		}
		pthread_mutex_unlock(&philo->eat_check);
		if (!return_dead(philo))
			makan(philo, thread_id);
		if (!return_dead(philo))
			tidur_fikir(philo, thread_id);
		++num_eat;
	}
	return (NULL);
}

void	check_dead(t_philo *philo)
{
	int	i;
	int	loop;

	loop = 1;
	while (loop)
	{
		i = -1;
		while (loop && ++i < philo->num)
		{
			pthread_mutex_lock(&philo->eat_check);
			if ((philo->check_full != -1 && \
				philo->check_full == philo->must_eat) || \
					get_time() - philo->last_eat[i] > philo->time_death)
			{
				loop = 0;
				philo->dead = 1;
			}
			pthread_mutex_unlock(&philo->eat_check);
			if ((philo->check_full != philo->must_eat) && return_dead(philo))
				print_dead(philo, i + 1);
			usleep(200);
		}
	}
}

void	run_thread(t_philo *philo)
{
	pthread_t	*thread;
	int			i;

	thread = malloc(sizeof(pthread_t) * philo->num);
	i = -1;
	while (++i < philo->num)
	{
		pthread_mutex_lock(&philo->eat_check);
		philo->index = i;
		philo->last_eat[i] = philo->start_time;
		pthread_mutex_unlock(&philo->eat_check);
		pthread_create(&(thread[i]), NULL, &routine, (void *)philo);
		usleep(1000);
	}
	check_dead(philo);
	i = -1;
	while (++i < philo->num)
		pthread_join(thread[i], NULL);
	free(thread);
}
