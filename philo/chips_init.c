/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chips_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:33:17 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/22 19:33:49 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_chips(t_diner *diner, t_philo *philo)
{
	unsigned int	id;
	unsigned int	pos;

	id = 0;
	pos = 0;
	while (id < philo->philosophers_counter)
	{
		if (id % 2 == 0 && pos < philo->philosophers_counter / 2)
			diner[id].chip = &philo->chips[pos++];
		else
			diner[id].chip = NULL;
		id ++;
	}
}
