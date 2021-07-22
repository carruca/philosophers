/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner_life_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:43:17 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/22 20:07:58 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*diner_life_loop(void *arg)
{
	t_diner		*diner;

	diner = arg;
	while (diner->parent->eat_done != diner->parent->philosophers_counter
		&& !diner->parent->philosopher_dead
		&& diner->time_to_alive > get_time())
	{
		if (diner->chip && hold_chopsticks(diner)
			&& eating(diner) && !count_eat(diner))
			sleeping(diner);
		usleep(1);
	}
	if (diner->parent->eat_done != diner->parent->philosophers_counter)
		set_dead(diner, "died");
	return (NULL);
}
