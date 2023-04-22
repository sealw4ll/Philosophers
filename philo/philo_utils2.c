/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 09:01:12 by codespace         #+#    #+#             */
/*   Updated: 2023/04/22 06:43:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_check(t_philo *philo)
{
	if (philo->num < 1)
		ft_putendl_fd("Invalid numbers of philosopher(s) (minimum 1)", 2);
	if (philo->time_death < 60)
		ft_putendl_fd("Invalid time_to_die (minimum 60)", 2);
	if (philo->time_eat < 60)
		ft_putendl_fd("Invalid time_to_eat (minimum 60)", 2);
	if (philo->time_sleep < 60)
		ft_putendl_fd("Invalid time_to_sleep (minimum 60)", 2);
	if (philo->must_eat < 0)
		ft_putendl_fd("Invalid num_of_times_philo_must_eat (minimum 0)", 2);
}

static void	ft_putnbr_fd(long long n, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		n += '0';
		write(fd, &n, 1);
	}
}

void	print_dead(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->eat_check);
	ft_putnbr_fd((get_time() - philo->start_time), 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(id, 1);
	ft_putstr_fd(" ", 1);
	ft_putendl_fd("died", 1);
	pthread_mutex_unlock(&philo->eat_check);
}

void	message(long long time, int thread_id, char *message, t_philo *philo)
{
	if (return_dead(philo))
		return ;
	pthread_mutex_lock(&philo->eat_check);
	// if (philo->dead)
	// {
	// 	pthread_mutex_unlock(&philo->eat_check);
	// 	return ;
	// }
	// pthread_mutex_unlock(&philo->eat_check);
	// pthread_mutex_lock(&philo->msg);
	ft_putnbr_fd((time - philo->start_time), 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(thread_id, 1);
	ft_putstr_fd(" ", 1);
	ft_putendl_fd(message, 1);
	pthread_mutex_unlock(&philo->eat_check);
}

int	timer(t_philo *philo,int action_time)
{
	long long	start;

	start = get_time();
	while (!philo->dead)
	{
		if (get_time() - start > (long long)action_time)
			return (1);
		usleep(50);
	}
	if (philo->dead)
		return (0);
	return (1);
}

void	free_funct(t_philo *philo)
{
	int i;

	i = -1;
	while (++i < philo->num)
		pthread_mutex_destroy(&(philo->fork[i]));
	free(philo->fork);
	free(philo->last_eat);
	pthread_mutex_destroy(&philo->msg);
	pthread_mutex_destroy(&philo->eat_check);
}

int	return_dead(t_philo *philo)
{
	int ret;
	
	ret = 0;
	pthread_mutex_lock(&philo->eat_check);
	if (philo->dead)
		ret = 1;
	pthread_mutex_unlock(&philo->eat_check);
	return (ret);
}
