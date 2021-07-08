#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "philo.h"
#include <stdlib.h>

//number_of_philosophers
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

/*
void	*print_id(void *arg)
{
	t_philo		*philo;

	philo = arg;
	pthread_mutex_lock(&philo->lock);
	philo->id++;
	printf("I am %i thread\n", philo->id);
	pthread_mutex_unlock(&philo->lock);
	return (NULL);
}*/

long int	get_time(void)
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
	t_philo	*philo;

	philo = arg;
	printf("Empieza a comer\n");
	usleep(1200000);
	printf("Termina de comer\n");
	printf("Han pasado %li millisegundos\n",get_msec_since_start(philo->start_time));
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
	printf("number of philosophers = %lu\n", philo->number_of_philosophers);
	printf("time to die = %lu\n", philo->time_to_die);
	printf("time to eat = %lu\n", philo->time_to_eat);
	printf("time to sleep = %lu\n", philo->time_to_sleep);
	printf("number of times each philosopher must eat = %lu\n",
		philo->number_of_times_each_philosopher_must_eat);
	printf("number of forks = %lu\n", philo->number_of_forks);
}

t_diner	*create_diner(t_philo *philo)
{
	t_diner	*diner;

	diner = ft_calloc(philo->number_of_philosophers, sizeof(t_diner));
	if (!diner)
		return (0);
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
		philo->number_of_philosophers = atoi(argv[1]);
		philo->time_to_die = atoi(argv[2]);
		philo->time_to_eat = atoi(argv[3]);
		philo->time_to_sleep = atoi(argv[4]);
		if (argc == 6)
			philo->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
		philo->number_of_forks = philo->number_of_philosophers;
		return (philo);
	}
	error("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (NULL);
}

int	create_loop(pthread_t *thread, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (pthread_create(&thread[i], NULL, eating, philo) == -1)
			return (error("pthread_create error\n"));
		i++;
	}
	return (0);
}

void	join_loop(pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		pthread_join(thread[i], NULL);
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
	print_arg(philo);
	philo->start_time = get_time();
	printf("start time = %li\n", philo->start_time);
//	pthread_mutex_init(&philo->lock, NULL);
//	if (create_loop(thread, philo))
		return (1);
//	pthread_mutex_destroy(&philo->lock);
//	join_loop(thread);
	system("leaks philo");
	return (0);
}
