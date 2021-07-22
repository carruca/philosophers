/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:31:48 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/22 19:32:22 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	count_eat(t_diner *diner)
{
	if (diner->parent->times_must_eat == diner->times_eat)
	{
		pthread_mutex_lock(&diner->parent->eat_mutex);
		diner->parent->eat_done++;
		pthread_mutex_unlock(&diner->parent->eat_mutex);
	}
	return (0);
}
