#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "philo.h"
#include <stdlib.h>

//philosophers_counter
//time_to_die
//time_to_eat
//time_to_sleep
//number_of_times_each_philosopher_must_eat
//number_of_forks

//eating
//thinking
//sleeping

void	eating(t_diner *diner)
{
	unsigned long	msec;

	msec = get_msec_since_start(diner->parent->start_time);
	printf("%lu %i is eating\n", msec, diner->id);
	usleep(diner->parent->time_to_eat * 1000);
}

void	thinking(t_diner *diner)
{
	unsigned long	msec;

	msec = get_msec_since_start(diner->parent->start_time);
	printf("%lu %i is thinking\n", msec, diner->id);
}

void	sleeping(t_diner *diner)
{
	unsigned long	msec;

	msec = get_msec_since_start(diner->parent->start_time);
	printf("%lu %i is sleeping\n", msec, diner->id);
	usleep(diner->parent->time_to_sleep * 1000);
}

void	set_chopstick(pthread_mutex_t *lock, _Bool *chopstick)
{
	pthread_mutex_lock(lock);
	*chopstick = 1;
	pthread_mutex_unlock(lock);
}

int	query_chopstick(_Bool *chopstick)
{
	if (*chopstick)
		return (1);
	return (0);
}

void	hold_chopsticks(t_diner *diner)
{
	int	ret;

	ret = 1;
	while (ret)
		ret = query_chopstick(diner->fork_right);
	set_chopstick(diner->lock_right, diner->fork_right);
	if (diner->parent->philosophers_counter > 1)
	{
		while (ret)
			ret = query_chopstick(diner->fork_left);
		set_chopstick(diner->lock_left, diner->fork_left);
	}
}

void	*diner_life_loop(void *arg)
{
	t_diner		*diner;

	diner = arg;
	while (1)
	{
		hold_chopsticks(diner);
		eating(diner);
		sleeping(diner);
		thinking(diner);
	}
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
	system("leaks philo");
	return (0);
}
