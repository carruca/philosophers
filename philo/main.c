/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 21:09:55 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/22 19:53:48 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_diner	*diner;

	philo = create_philo(argc, argv);
	if (!philo)
		return (1);
	diner = diner_create(philo);
	if (mutex_init_loop(philo))
		return (1);
	if (thread_create_loop(diner, philo))
		return (1);
	thread_join_loop(diner);
	mutex_destroy_loop(philo);
	pthread_mutex_destroy(&philo->print_mutex);
	pthread_mutex_destroy(&philo->dead_mutex);
	pthread_mutex_destroy(&philo->eat_mutex);
	philo_free(&philo, &diner);
	return (0);
}
