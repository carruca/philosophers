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

void	*eating(void *arg)
{
	t_diner	*diner;

	diner = arg;
	printf("%i empieza a comer\n", diner->id);
	usleep(diner->parent->time_to_eat * 1000);
	printf("%i termina de comer\n", diner->id);
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
	system("leaks philo");
	return (0);
}
