/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:03:03 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/22 19:03:48 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_diner *diner, char *status)
{
	unsigned int	msec;

	msec = get_msec_since_start(diner->parent->start_time);
	pthread_mutex_lock(&diner->parent->print_mutex);
	if (!diner->parent->philosopher_dead)
		printf("%u %i %s\n", msec, diner->id, status);
	pthread_mutex_unlock(&diner->parent->print_mutex);
}
