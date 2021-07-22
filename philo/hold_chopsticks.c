/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hold_chopsticks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:15:57 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/22 19:17:54 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	hold_chopsticks(t_diner *diner)
{
	if (diner->parent->philosophers_counter > 1)
	{
		if (set_chopsticks(diner, 1))
		{
			print_status(diner, "has taken a fork");
			print_status(diner, "has taken a fork");
			give_chip_to_right(diner);
			return (1);
		}
	}
	return (0);
}
