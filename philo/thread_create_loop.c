/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create_loop.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:13:02 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/22 17:51:23 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_create_loop(t_diner *diner, t_philo *philo)
{
	unsigned int	id;

	id = 0;
	init_chips(diner, philo);
	while (id < philo->philosophers_counter)
	{
		if (pthread_create(&diner[id].thread, NULL,
				diner_life_loop, &diner[id]) == -1)
			return (error("pthread_create error\n"));
		id++;
	}
	return (0);
}
