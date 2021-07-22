/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 18:58:57 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/22 18:59:28 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dsleep(unsigned int time_to_sleep)
{
	unsigned long	time_to_stop;

	time_to_stop = get_time() + time_to_sleep;
	while (get_time() < time_to_stop)
		usleep(500);
}
