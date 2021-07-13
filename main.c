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

	pthread_mutex_lock(&diner->parent->print_mutex);
	msec = get_msec_since_start(diner->parent->start_time);
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

int	hold_chopsticks(t_diner *diner)
{
	if (diner->parent->philosophers_counter > 1)
	{
		if (set_chopsticks(diner, 1))
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
		print_status(diner, str);
	diner->parent->philosopher_dead = 1;
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
	philo->start_time = get_time();
	diner = diner_create(philo);
	if (mutex_init_loop(philo))
		return (1);
	if (thread_create_loop(diner, philo))
		return (1);
	mutex_destroy_loop(philo);
	pthread_mutex_destroy(&philo->print_mutex);
	pthread_mutex_destroy(&philo->dead_mutex);
	thread_join_loop(diner);
//	system("leaks philo");
	return (0);
}
