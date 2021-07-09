/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:17:05 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/09 17:44:35 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

unsigned long	get_time(void)
{
	unsigned long	msec;
	struct timeval	tvp;

	if (gettimeofday(&tvp, NULL) == -1)
		return (error("gettimeofday error\n"));
	msec = (tvp.tv_sec * 1000) + (tvp.tv_usec / 1000);
	return (msec);
}
