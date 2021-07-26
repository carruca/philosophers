/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_destroy_loop.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:10:02 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/09 17:51:25 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_destroy_loop(t_philo *philo)
{
	unsigned int	pos;

	pos = 0;
	while (pos < philo->chopsticks_counter)
	{
		pthread_mutex_destroy(&philo->locks[pos]);
		pos++;
	}
	pthread_mutex_destroy(&philo->print_mutex);
	pthread_mutex_destroy(&philo->dead_mutex);
	pthread_mutex_destroy(&philo->eat_mutex);
}
