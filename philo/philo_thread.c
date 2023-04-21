/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:19:04 by codespace         #+#    #+#             */
/*   Updated: 2023/04/21 13:22:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	makan(t_philo *philo, int thread_id)
{
	pthread_mutex_lock(&(philo->fork[thread_id]));
	pthread_mutex_lock(&(philo->fork[(thread_id + 1) % philo->num]));
	message(get_time(), thread_id + 1, "has taken a fork", philo);
	message(get_time(), thread_id + 1, "has taken a fork", philo);
	message(get_time(), thread_id + 1, "is eating", philo);
	pthread_mutex_lock(&philo->eat_check);
	philo->last_eat[thread_id] = get_time();
	pthread_mutex_unlock(&philo->eat_check);
	pthread_mutex_lock(&(philo->fork[thread_id]));
	pthread_mutex_lock(&(philo->fork[(thread_id + 1) % philo->num]));
	timer(philo, philo->time_eat);
}

void	tidur_fikir(t_philo *philo, int thread_id)
{
	message(get_time(), thread_id + 1, "is sleeping", philo);
	timer(philo, philo->time_sleep);
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
	while (!philo->dead)
	{
		pthread_mutex_lock(&philo->eat_check);
		if (philo->check_full >= 0 && num_eat == philo->must_eat)
		{
			++philo->check_full;
			break ;
		}
		pthread_mutex_unlock(&philo->eat_check);
		makan(philo, thread_id);
		tidur_fikir(philo, thread_id);
		++num_eat;
	}
	return (NULL);
}

void	check_dead(t_philo *philo)
{
	int i;
	int loop;

	loop = 1;
	while (loop)
	{
		i = -1;
		while (loop && ++i < philo->num)
		{
			pthread_mutex_lock(&philo->eat_check);
			if (get_time() - philo->last_eat[i] > philo->time_death)
			{
				philo->dead = 1;
				loop = 0;
				message(get_time(), i + 1, "died", philo);
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
		philo->index = i;
		pthread_create(&(thread[i]), NULL, &routine, (void *)philo);
	}
	check_dead(philo);
	i = -1;
	while (++i < philo->num)
		pthread_join(thread[i], NULL);
}
