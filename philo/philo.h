#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <limits.h>

typedef struct s_philo
{
	int				index;
	int             num;
	int             time_death;
	int             time_eat;
	int             time_sleep;
	int             check_full;
	int             must_eat;
	int				dead;
	long long       start_time;
	long long		*last_eat;
	pthread_mutex_t msg;
	pthread_mutex_t eat_check;
	pthread_mutex_t *fork;
}   t_philo;

// utils
int 		ft_atoi(const char *str);
int 		ft_strlen(const char *s);
long long	get_time();
void		ft_putendl_fd(char *s, int fd);
void		ft_putstr_fd(char *s, int fd);
void		message(long long time, int thread_id, char *message, t_philo *philo);
void		timer(t_philo *philo ,int action_time);
void		free_exit(t_philo *philo);

//main
void	error_check(t_philo *philo);

//thread
void	run_thread(t_philo *philo);
void	check_dead(t_philo *philo);

#endif