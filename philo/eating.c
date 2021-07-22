/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:30:33 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/22 19:31:04 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_diner *diner)
{
	print_status(diner, "is eating");
	diner->time_to_alive = get_time() + diner->parent->time_to_die;
	if (diner->time_to_alive < get_time() + diner->parent->time_to_eat)
	{
		dsleep(diner->parent->time_to_die);
		set_dead(diner, "died");
		set_chopsticks(diner, 0);
		return (0);
	}
	dsleep(diner->parent->time_to_eat);
	set_chopsticks(diner, 0);
	diner->times_eat++;
	return (1);
}
