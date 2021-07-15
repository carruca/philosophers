/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_join_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:14:38 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/09 17:49:59 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_join_loop(t_diner *diner)
{
	unsigned int	id;

	id = 0;
	while (id < diner->parent->philosophers_counter)
	{
		pthread_mutex_lock(&diner->parent->eat_mutex);
		id++;
	}
	id = 0;
	while (id < diner->parent->philosophers_counter)
	{
		pthread_join(diner[id].thread, NULL);
		id++;
	}
}
