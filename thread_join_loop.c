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
	unsigned int	pos;

	pos = 0;
	while (pos < diner->parent->philosophers_counter)
	{
		pthread_join(diner[pos].thread, NULL);
		pos++;
	}
}
