/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_locks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:27:55 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/09 17:36:01 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_locks(
		unsigned pos, unsigned counter, t_diner *diner, pthread_mutex_t *locks)
{
	if (pos == counter - 1)
		diner->lock_right = &locks[0];
	else
		diner->lock_right = &locks[pos];
	if (pos == 0)
		diner->lock_left = &locks[counter - 1];
	else
		diner->lock_left = &locks[pos - 1];
}
