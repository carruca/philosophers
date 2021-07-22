/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 19:44:39 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/22 19:45:16 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_free(t_philo **philo, t_diner **diner)
{
	free(*diner);
	free((*philo)->locks);
	free((*philo)->forks);
	free((*philo)->chips);
	free(*philo);
}
