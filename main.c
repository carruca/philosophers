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

int	error(char *msg)
{
	write(2, msg, strlen(msg));
	return (1);
}

unsigned long	get_time(void)
{
	unsigned long	msec;
	struct timeval	tvp;

	if (gettimeofday(&tvp, NULL) == -1)
		return (error("gettimeofday error\n"));
	msec = (tvp.tv_sec * 1000) + (tvp.tv_usec / 1000);
	return (msec);
}

unsigned long	get_msec_since_start(unsigned long start_time)
{
	unsigned long	current_time;

	current_time = get_time();
	return (current_time - start_time);
}

void	*eating(void *arg)
{
	t_diner	*diner;

	diner = arg;
	printf("%i empieza a comer\n", diner->id);
	usleep(diner->parent->time_to_eat * 1000);
	printf("%i termina de comer\n", diner->id);
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*dst;

	dst = malloc(count * size);
	if (!dst)
		return (NULL);
	memset(dst, 0, count * size);
	return (dst);
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

void	assign_chopsticks(unsigned pos, unsigned counter, t_diner *diner, _Bool *forks)
{
	if (pos == counter - 1)
		diner->fork_right = &forks[0];
	else
		diner->fork_right = &forks[pos];
	if (pos == 0)
		diner->fork_left = &forks[counter - 1];
	else
		diner->fork_left = &forks[pos - 1];
}

void	assign_locks(
		unsigned pos, unsigned counter, t_diner *diner, pthread_mutex_t *locks)
{
	if (pos == counter - 1)
		diner->lock_right = &locks[0];
	else
		diner->lock_right = &locks[pos];
	if (pos == 0)
		diner->lock_left = &locks[counter - 1];
	else
		diner->lock_left = &locks[pos - 1];
}

t_diner	*create_diner(t_philo *philo)
{
	t_diner		*diner;
	unsigned	pos;

	diner = ft_calloc(philo->philosophers_counter, sizeof(t_diner));
	if (!diner)
		return (NULL);
	pos = 0;
	while (pos < philo->philosophers_counter)
	{
		diner[pos].id = pos;
		diner[pos].parent = philo;
		assign_chopsticks(pos, philo->chopsticks_counter,
			&diner[pos], philo->forks);
		assign_locks(pos, philo->chopsticks_counter,
			&diner[pos], philo->locks);
		pos++;
	}
	return (diner);
}

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

int	create_thread_loop(t_diner *diner, t_philo *philo)
{
	unsigned	i;

	i = 0;
	while (i < philo->philosophers_counter)
	{
		if (pthread_create(&diner[i].thread, NULL, eating, &diner[i]) == -1)
			return (error("pthread_create error\n"));
		i++;
	}
	return (0);
}

void	join_thread_loop(t_diner *diner)
{
	unsigned	i;

	i = 0;
	while (i < diner->parent->philosophers_counter)
	{
		pthread_join(diner[i].thread, NULL);
		i++;
	}
}

int	mutex_init_loop(t_philo *philo)
{
	unsigned	i;

	i = 0;
	while (i < philo->chopsticks_counter)
	{
		if (pthread_mutex_init(&philo->locks[i], NULL))
			return (error("pthread_mutex_init error\n"));
		i++;
	}
	return (0);
}

void	mutex_destroy_loop(t_philo *philo)
{
	unsigned	i;

	i = 0;
	while (i < philo->chopsticks_counter)
	{
		pthread_mutex_destroy(&philo->locks[i]);
		i++;
	}
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
	diner = create_diner(philo);
	if (mutex_init_loop(philo))
		return (1);
	if (create_thread_loop(diner, philo))
		return (1);
	mutex_destroy_loop(philo);
	join_thread_loop(diner);
	system("leaks philo");
	return (0);
}
