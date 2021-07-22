/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:08:06 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/09 17:50:59 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_init_loop(t_philo *philo)
{
	unsigned int	pos;

	pos = 0;
	while (pos < philo->chopsticks_counter)
	{
		if (pthread_mutex_init(&philo->locks[pos], NULL))
			return (error("pthread_mutex_init error\n"));
		pos++;
	}
	return (0);
}
