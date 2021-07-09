/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create_loop.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:13:02 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/09 17:50:32 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_create_loop(t_diner *diner, t_philo *philo)
{
	unsigned int	pos;

	pos = 0;
	while (pos < philo->philosophers_counter)
	{
		if (pthread_create(&diner[pos].thread, NULL, eating, &diner[pos]) == -1)
			return (error("pthread_create error\n"));
		pos++;
	}
	return (0);
}
