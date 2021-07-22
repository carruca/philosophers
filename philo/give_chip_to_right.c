/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   give_chip_to_right.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:07:36 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/22 19:09:41 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	give_chip_to_right(t_diner *diner)
{
	t_diner	*right_diner;

	if (diner->id == diner->parent->philosophers_counter)
		right_diner = diner - (diner->id - 1);
	else
		right_diner = diner + 1;
	right_diner->chip = diner->chip;
	diner->chip = NULL;
}
