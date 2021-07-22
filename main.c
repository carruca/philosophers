/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 21:09:55 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/15 21:29:01 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "philo.h"
#include <stdlib.h>

void	dsleep(unsigned int time_to_sleep)
{
	unsigned long	time_to_stop;

	time_to_stop = get_time() + time_to_sleep;
	while (get_time() < time_to_stop)
		usleep(500);
}

void	print_status(t_diner *diner, char *status)
{
	unsigned int	msec;

	msec = get_msec_since_start(diner->parent->start_time);
	pthread_mutex_lock(&diner->parent->print_mutex);
	if (!diner->parent->philosopher_dead)
		printf("%u %i %s\n", msec, diner->id, status);
	pthread_mutex_unlock(&diner->parent->print_mutex);
}

int	set_chopsticks(t_diner *diner, _Bool value)
{
	int ret;

	pthread_mutex_lock(diner->lock_left);
	pthread_mutex_lock(diner->lock_right);
	if (*diner->fork_right != value && *diner->fork_left != value)
	{
		*diner->fork_right = value;
		*diner->fork_left = value;
		ret = 1;
	}
	else
		ret = 0;
	pthread_mutex_unlock(diner->lock_right);
	pthread_mutex_unlock(diner->lock_left);
	return (ret);
}

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

int	hold_chopsticks(t_diner *diner)
{
	if (diner->parent->philosophers_counter > 1)
	{
		if (set_chopsticks(diner, 1))
		{
			print_status(diner, "has taken a fork");
			print_status(diner, "has taken a fork");
			give_chip_to_right(diner);
			return (1);
		}
	}
	return (0);
}

void	set_dead(t_diner *diner, char *str)
{
	pthread_mutex_lock(&diner->parent->dead_mutex);
	if (!diner->parent->philosopher_dead)
	{
		print_status(diner, str);
		diner->parent->philosopher_dead = 1;
	}
	pthread_mutex_unlock(&diner->parent->dead_mutex);
}

void	sleeping(t_diner *diner)
{
	print_status(diner, "is sleeping");
	if (diner->time_to_alive < get_time() + diner->parent->time_to_sleep)
	{
		dsleep(diner->time_to_alive - get_time());
		set_dead(diner, "died while sleeping");
		return ;
	}
	dsleep(diner->parent->time_to_sleep);
	print_status(diner, "is thinking");
}

int	eating(t_diner *diner)
{
	print_status(diner, "is eating");
	diner->time_to_alive = get_time() + diner->parent->time_to_die;
	if (diner->time_to_alive < get_time() + diner->parent->time_to_eat)
	{
		dsleep(diner->parent->time_to_die);
		set_dead(diner, "died while eating");
		set_chopsticks(diner, 0);
		return (0);
	}
	dsleep(diner->parent->time_to_eat);
	set_chopsticks(diner, 0);
	diner->times_eat++;
	printf("%i has eaten %i times\n", diner->id, diner->times_eat);
	return (1);
}

int	count_eat(t_diner *diner)
{
	if (diner->parent->times_must_eat == diner->times_eat)
	{
		pthread_mutex_lock(&diner->parent->eat_mutex);
		diner->parent->eat_done++;
//		print_status(diner, "has enough to eat");
		pthread_mutex_unlock(&diner->parent->eat_mutex);
	}
	return (0);
}

void	init_chips(t_diner *diner, t_philo *philo)
{
	unsigned int	id;
	unsigned int	pos;

	id = 0;
	pos = 0;
	while (id < philo->philosophers_counter)
	{
		if (id % 2 == 0 && pos < philo->philosophers_counter / 2)
			diner[id].chip = &philo->chips[pos++];
		else
			diner[id].chip = NULL;
		id ++;
	}
}

void	*diner_life_loop(void *arg)
{
	t_diner		*diner;

	diner = arg;
	while (diner->parent->eat_done != diner->parent->philosophers_counter
		&& !diner->parent->philosopher_dead
		&& diner->time_to_alive > get_time())
	{
		if (diner->chip && hold_chopsticks(diner) && eating(diner) && !count_eat(diner))
			sleeping(diner);
		usleep(1);
	}
	if (diner->parent->eat_done != diner->parent->philosophers_counter)
		set_dead(diner, "died while life loop");
	return (NULL);
}

void	print_arg(t_philo *philo)
{
	printf("number of philosophers = %u\n", philo->philosophers_counter);
	printf("time to die = %lu\n", philo->time_to_die);
	printf("time to eat = %lu\n", philo->time_to_eat);
	printf("time to sleep = %lu\n", philo->time_to_sleep);
	printf("number of times each philosopher must eat = %u\n",
		philo->times_must_eat);
	printf("number of forks = %u\n", philo->chopsticks_counter);
}

void	free_philo(t_philo **philo, t_diner **diner)
{
	free(*diner);
	free((*philo)->locks);
	free((*philo)->forks);
	free((*philo)->chips);
	free(*philo);
}

void	leaks_check(void)
{
	system("leaks philo");
}

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
	free_philo(&philo, &diner);
	return (0);
}
