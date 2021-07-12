/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_msec_since_start.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:19:27 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/12 18:08:10 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned	get_msec_since_start(unsigned long start_time)
{
	unsigned long	current_time;

	current_time = get_time();
	return (current_time - start_time);
}
