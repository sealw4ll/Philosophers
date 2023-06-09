/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:19:04 by codespace         #+#    #+#             */
/*   Updated: 2023/04/25 18:48:44 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	makan(t_philo *philo, int thread_id, int *num_eat)
{
	pthread_mutex_lock(&(philo->fork[thread_id]));
	message(get_time(), thread_id + 1, "has taken a fork", philo);
	pthread_mutex_lock(&(philo->fork[((thread_id + 1) % philo->num)]));
	message(get_time(), thread_id + 1, "has taken a fork", philo);
	message(get_time(), thread_id + 1, "is eating", philo);
	pthread_mutex_lock(&philo->eat_check);
	philo->last_eat[thread_id] = get_time();
	*num_eat += 1;
	if (philo->check_full >= 0 && *num_eat == philo->must_eat)
		++philo->check_full;
	pthread_mutex_unlock(&philo->eat_check);
	timer (philo, philo->time_eat);
	pthread_mutex_unlock(&(philo->fork[thread_id]));
	pthread_mutex_unlock(&(philo->fork[((thread_id + 1) % philo->num)]));
}

void	tidur_fikir(t_philo *philo, int thread_id)
{
	message(get_time(), thread_id + 1, "is sleeping", philo);
	timer (philo, philo->time_sleep);
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
	while (!return_dead(philo))
	{
		if (!return_dead(philo))
			makan(philo, thread_id, &num_eat);
		if (!return_dead(philo))
			tidur_fikir(philo, thread_id);
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
			if (get_time() - philo->last_eat[i] > philo->time_death)
			{
				loop = 0;
				philo->dead = 1;
				print_dead(philo, i + 1);
			}
			else if (philo->check_full == philo->num)
			{
				loop = 0;
				philo->dead = 1;
			}
			pthread_mutex_unlock(&philo->eat_check);
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
		usleep(100);
	}
	check_dead(philo);
	i = -1;
	while (++i < philo->num)
		pthread_join(thread[i], NULL);
	free(thread);
}
