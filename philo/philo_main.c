/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 06:29:12 by codespace         #+#    #+#             */
/*   Updated: 2023/04/21 14:32:23 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_thread(t_philo *philo)
{
	int	i;

	philo->fork = malloc(sizeof(pthread_mutex_t) * philo->num);
	i = -1;
	while (++i < philo->num)
		pthread_mutex_init(&(philo->fork[i]), NULL);
	pthread_mutex_init(&(philo->msg), NULL);
	pthread_mutex_init(&(philo->eat_check), NULL);
}

void	init_vars(t_philo *philo, int ac, char **av)
{
	philo->num = ft_atoi(av[1]);
	philo->time_death = ft_atoi(av[2]);
	philo->time_eat = ft_atoi(av[3]);
	philo->time_sleep = ft_atoi(av[4]);
	philo->start_time = get_time();
	philo->dead = 0;
	philo->last_eat = malloc(sizeof(long long) * philo->num);
	if (ac == 6)
	{
		philo->must_eat = ft_atoi(av[5]);
		philo->check_full = 0;
	}
	else
	{
		philo->must_eat = -1;
		philo->check_full = -1;
	}
	if (philo->num < 1 || philo->time_death < 60 || philo->time_eat < 60 || \
		philo->time_sleep < 60 || philo->must_eat < -1)
	{
		ft_putendl_fd("Error: invalid input", 2);
		error_check(philo);
		exit (1);
	}
	init_thread(philo);
	return ;
}

int	main(int ac, char **av)
{
	t_philo			philo;

	if (ac != 5 && ac != 6)
	{
		ft_putendl_fd("Error: invalid number of arguments", 2);
		ft_putstr_fd("expected input: [num_of_philo] [time_to_die] ", 2);
		ft_putendl_fd("[time_to_eat] [time_to_sleep]", 2);
		ft_putendl_fd("optional argument(s): {num_of_times_philo_must_eat}", 2);
		return (1);
	}
	init_vars(&philo, ac, av);
	run_thread(&philo);
	free_funct(&philo);
	return (0);
}
