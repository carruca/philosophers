/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_chopsticks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:27:36 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/12 20:08:58 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_chopsticks(
		unsigned pos,
		unsigned counter,
		t_diner *diner,
		_Bool *forks)
{
	diner->fork_right = &forks[pos];
	if (pos == 0)
		diner->fork_left = &forks[counter - 1];
	else
		diner->fork_left = &forks[pos - 1];
}
