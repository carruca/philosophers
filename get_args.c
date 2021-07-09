/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:22:19 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/09 17:44:05 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

t_philo	*get_args(int argc, char **argv)
{
	t_philo	*philo;

	if (argc > 4 && argc < 7)
	{
//		if (check_error())
		philo = ft_calloc(1, sizeof(t_philo));
		if (!philo)
			return (NULL);
		philo->philosophers_counter = atoi(argv[1]);
		philo->time_to_die = atoi(argv[2]);
		philo->time_to_eat = atoi(argv[3]);
		philo->time_to_sleep = atoi(argv[4]);
		if (argc == 6)
			philo->eat_counter = atoi(argv[5]);
		philo->chopsticks_counter = philo->philosophers_counter;
		return (philo);
	}
	error("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (NULL);
}
