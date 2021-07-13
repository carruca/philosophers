/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:26:01 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/12 20:40:40 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

t_diner	*diner_create(t_philo *philo)
{
	t_diner			*diner;
	unsigned int	id;

	diner = ft_calloc(philo->philosophers_counter, sizeof(t_diner));
	if (!diner)
		return (NULL);
	id = 0;
	while (id < philo->philosophers_counter)
	{
		diner[id].id = id;
		diner[id].parent = philo;
		assign_chopsticks(id, philo->chopsticks_counter,
			&diner[id], philo->forks);
		assign_locks(id, philo->chopsticks_counter,
			&diner[id], philo->locks);
		diner[id].time_to_alive = philo->start_time + philo->time_to_die;
		id++;
	}
	return (diner);
}
