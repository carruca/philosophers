/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 21:09:55 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/22 23:45:11 by tsierra-         ###   ########.fr       */
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
	thread_join_loop(diner, philo);
	mutex_destroy_loop(philo);
	philo_free(&philo, &diner);
	return (0);
}
