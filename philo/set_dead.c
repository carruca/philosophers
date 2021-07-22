/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dead.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:18:52 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/22 19:19:26 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_dead(t_diner *diner, char *str)
{
	pthread_mutex_lock(&diner->parent->dead_mutex);
	if (!diner->parent->philosopher_dead)
	{
		print_status(diner, str);
		diner->parent->philosopher_dead = 1;
	}
	pthread_mutex_unlock(&diner->parent->dead_mutex);
}
