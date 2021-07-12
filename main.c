#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "philo.h"
#include <stdlib.h>

void	print_status(t_diner *diner, char *status)
{
	unsigned int	msec;

	pthread_mutex_lock(&diner->parent->print_mutex);
	msec = get_msec_since_start(diner->parent->start_time);
	if (!diner->parent->philosopher_dead)
		printf("%u %i %s\n", msec, diner->id, status);
	pthread_mutex_unlock(&diner->parent->print_mutex);
}

_Bool	set_chopstick(t_diner *diner, _Bool value)
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

int	hold_chopsticks(t_diner *diner)
{
	if (diner->parent->philosophers_counter > 1)
	{
		if (set_chopstick(diner, 1))
		{
			print_status(diner, "has taken a fork");
			print_status(diner, "has taken a fork");
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
		print_status(diner, "died");
		printf("alive = %lu current = %lu diff = %lu\n", diner->time_to_alive, get_time(), get_time() - diner->time_to_alive);
		print_status(diner, str);
	}
	diner->parent->philosopher_dead = 1;
	pthread_mutex_unlock(&diner->parent->dead_mutex);
}

void	sleeping(t_diner *diner)
{
	print_status(diner, "is sleeping");
	if (diner->time_to_alive < get_time() + diner->parent->time_to_sleep)
	{
		usleep((get_time() + diner->parent->time_to_sleep - diner->time_to_alive) * 1000);
		set_dead(diner, "while sleeping");
		return ;
	}
	usleep(diner->parent->time_to_sleep * 1000);
	print_status(diner, "is thinking");
}

int	eating(t_diner *diner)
{
	diner->time_to_alive = get_time() + diner->parent->time_to_die;
	print_status(diner, "is eating");
	if (diner->time_to_alive < get_time() + diner->parent->time_to_eat)
	{
		usleep(diner->parent->time_to_die * 1000);
		set_dead(diner, "while eating");
		set_chopstick(diner, 0);
		return (0);
	}
	usleep(diner->parent->time_to_eat * 1000);
	set_chopstick(diner, 0);
	return (1);
}


void	*diner_life_loop(void *arg)
{
	t_diner		*diner;

	diner = arg;
	while (!diner->parent->philosopher_dead && diner->time_to_alive > get_time())
	{
		if (hold_chopsticks(diner) && eating(diner))
			sleeping(diner);
		usleep(1);
	}
	set_dead(diner, "while loop");
	return (NULL);
}

void	print_arg(t_philo *philo)
{
	printf("number of philosophers = %u\n", philo->philosophers_counter);
	printf("time to die = %lu\n", philo->time_to_die);
	printf("time to eat = %lu\n", philo->time_to_eat);
	printf("time to sleep = %lu\n", philo->time_to_sleep);
	printf("number of times each philosopher must eat = %u\n",
		philo->eat_counter);
	printf("number of forks = %u\n", philo->chopsticks_counter);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_diner	*diner;

	philo = get_args(argc, argv);
	if (!philo)
		return (1);
	philo->forks = ft_calloc(philo->chopsticks_counter, sizeof(_Bool));
	if (!philo->forks)
		return (1);
	philo->locks = ft_calloc(philo->chopsticks_counter, sizeof(pthread_mutex_t));
	if (!philo->locks)
		return (1);
	print_arg(philo);
	philo->start_time = get_time();
	printf("start time = %li\n", philo->start_time);
	diner = diner_create(philo);
	if (mutex_init_loop(philo))
		return (1);
	if (thread_create_loop(diner, philo))
		return (1);
	mutex_destroy_loop(philo);
	thread_join_loop(diner);
//	system("leaks philo");
	return (0);
}
