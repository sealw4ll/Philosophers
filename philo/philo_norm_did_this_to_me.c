/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_norm_did_this_to_me.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wting <wting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 12:25:57 by codespace         #+#    #+#             */
/*   Updated: 2023/04/25 18:49:58 by wting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	timer(t_philo *philo, int action_time)
{
	long long	start;

	start = get_time();
	while (!return_dead(philo))
	{
		if (get_time() - start >= action_time)
			return ;
		usleep(40);
	}
}

int	normed(t_philo *philo, int index, int *loop)
{
	if (get_time() - philo->last_eat[index] > philo->time_death)
	{
		*loop = 0;
		philo->dead = 1;
		return (1);
	}
	if (philo->check_full == philo->must_eat)
	{
		*loop = 0;
		philo->dead = 1;
		return (2);
	}
	return (0);
}
