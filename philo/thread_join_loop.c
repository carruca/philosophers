/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_join_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:14:38 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/22 23:45:35 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	thread_join_loop(t_diner *diner, t_philo *philo)
{
	unsigned int	id;

	id = 0;
	while (id < philo->philosophers_counter)
	{
		pthread_join(diner[id].thread, NULL);
		id++;
	}
}
