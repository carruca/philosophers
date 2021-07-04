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

//Eating
//Thinking
//Sleeping

int	error(char *msg)
{
	write(2, msg, sizeof(msg));
	return (1);
}

void	*print_id(void *arg)
{
	t_philo	*philo;

	philo = arg;
	pthread_mutex_lock(&philo->lock);
	printf("I am %i thread\n", philo->id);
	pthread_mutex_unlock(&philo->lock);
	return (NULL);
}

long int	get_milliseconds(void)
{
	unsigned long	msec;
	struct timeval	tvp;

	if (gettimeofday(&tvp, NULL) == -1)
		return (error("gettimeofday error\n"));
	msec = tvp.tv_sec * 1000;
	return (msec);
}

void	*eating(void *arg)
{
	printf("Empieza a comer\n");
	usleep(100000);
	printf("Termina de comer\n");
	return (NULL);
}

int	main()
{
	t_philo			philo;
	pthread_t		thread[4];
	long int	msec;
	int		i;
	
	memset(&philo, 0, sizeof(pthread_mutex_t));
	msec = get_milliseconds();
	printf("milliseconds = %li\n", msec);
	pthread_mutex_init(&philo.lock, NULL);
	i = 0;
	while (i < 4)
	{
		philo.id = i;
		printf("philo id = %i\n", philo.id);
		if (pthread_create(&thread[i], NULL, print_id, &philo) == -1)
			return (error("pthread_create error\n"));
		i++;
	}
	pthread_mutex_destroy(&philo.lock);
	i = 0;
	while (i < 4)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	system("leaks philo");
	return (0);
}
