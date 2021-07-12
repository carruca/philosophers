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
	unsigned int	pos;

	diner = ft_calloc(philo->philosophers_counter, sizeof(t_diner));
	if (!diner)
		return (NULL);
	pos = 0;
	while (pos < philo->philosophers_counter)
	{
		diner[pos].id = pos;
		diner[pos].parent = philo;
		assign_chopsticks(pos, philo->chopsticks_counter,
			&diner[pos], philo->forks);
		assign_locks(pos, philo->chopsticks_counter,
			&diner[pos], philo->locks);
		diner[pos].time_to_alive = philo->start_time + philo->time_to_die;
		printf("%lu = time_to_alive\n", diner[pos].time_to_alive);
		pos++;
	}
	return (diner);
}
