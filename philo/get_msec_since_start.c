/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_msec_since_start.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:19:27 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/22 17:49:27 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_msec_since_start(unsigned long start_time)
{
	unsigned int	current_time;

	current_time = get_time();
	return (current_time - start_time);
}
