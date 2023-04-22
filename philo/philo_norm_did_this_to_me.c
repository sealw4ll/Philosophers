/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_norm_did_this_to_me.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 12:25:57 by codespace         #+#    #+#             */
/*   Updated: 2023/04/22 15:09:06 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
