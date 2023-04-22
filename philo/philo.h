/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 11:36:06 by codespace         #+#    #+#             */
/*   Updated: 2023/04/22 15:37:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_philo
{
	int				index;
	int				num;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				check_full;
	int				must_eat;
	int				dead;
	long long		start_time;
	long long		*last_eat;
	pthread_mutex_t	msg;
	pthread_mutex_t	eat_check;
	pthread_mutex_t	*fork;
}	t_philo;

// utils
int			ft_atoi(const char *str);
int			ft_strlen(const char *s);
long long	get_time(void);
void		ft_putendl_fd(char *s, int fd);
void		ft_putstr_fd(char *s, int fd);
void		message(long long time, int thread_id, \
	char *message, t_philo *philo);
int			timer(t_philo *philo, int action_time);
void		free_funct(t_philo *philo);
void		ft_putnbr_fd(long long n, int fd);

//main
void		error_check(t_philo *philo);
void		print_dead(t_philo *philo, int id);

//thread
void		run_thread(t_philo *philo);
void		check_dead(t_philo *philo);
int			return_dead(t_philo *philo);

#endif