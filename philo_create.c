#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

static void	fill_philo(t_philo *philo, int argc, char **argv)
{
	philo->philosophers_counter = atoi(argv[1]);
	philo->time_to_die = atoi(argv[2]);
	philo->time_to_eat = atoi(argv[3]);
	philo->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		philo->times_must_eat = atoi(argv[5]);
	else
		philo->times_must_eat = -1;
	philo->chopsticks_counter = philo->philosophers_counter;
}

static void	init_mutex_philo(t_philo *philo)
{
	pthread_mutex_init(&philo->print_mutex, NULL);
	pthread_mutex_init(&philo->dead_mutex, NULL);
	pthread_mutex_init(&philo->eat_mutex, NULL);
}

static int	check_error(char **argv)
{
	argv++;
	while (*argv)
	{
		if (!ft_strdigit(*argv) || ft_strneg(*argv))
			return (1);
		argv++;
	}
	return (0);
}

t_philo	*create_philo(int argc, char **argv)
{
	t_philo	*philo;

	if (argc < 5 || argc > 6 || check_error(argv))
	{
		error("Wrong arguments\n");
		return (NULL);
	}
	philo = ft_calloc(1, sizeof(t_philo));
	if (!philo)
		return (NULL);
	fill_philo(philo, argc, argv);
	init_mutex_philo(philo);
	philo->forks = ft_calloc(philo->chopsticks_counter, sizeof(_Bool));
	if (!philo->forks)
		return (NULL);
	philo->locks = ft_calloc(philo->chopsticks_counter,
			sizeof(pthread_mutex_t));
	if (!philo->locks)
		return (NULL);
	philo->chips = ft_calloc(philo->philosophers_counter / 2,
			sizeof(_Bool));
	if (!philo->chips)
		return (NULL);
	philo->start_time = get_time();
	return (philo);
}
