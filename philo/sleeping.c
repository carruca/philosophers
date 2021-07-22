/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:28:51 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/22 19:29:17 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_diner *diner)
{
	print_status(diner, "is sleeping");
	if (diner->time_to_alive < get_time() + diner->parent->time_to_sleep)
	{
		dsleep(diner->time_to_alive - get_time());
		set_dead(diner, "died");
		return ;
	}
	dsleep(diner->parent->time_to_sleep);
	print_status(diner, "is thinking");
}
