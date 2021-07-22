/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_chopsticks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:04:46 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/22 20:09:21 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_chopsticks(t_diner *diner, _Bool value)
{
	int	ret;

	pthread_mutex_lock(diner->lock_left);
	pthread_mutex_lock(diner->lock_right);
	if (*diner->fork_right != value && *diner->fork_left != value)
	{
		*diner->fork_right = value;
		*diner->fork_left = value;
		ret = 1;
	}
	else
		ret = 0;
	pthread_mutex_unlock(diner->lock_right);
	pthread_mutex_unlock(diner->lock_left);
	return (ret);
}
