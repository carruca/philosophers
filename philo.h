#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_diner
{
	unsigned			id;
	pthread_t		thread;
	_Bool				*fork_right;
	_Bool				*fork_left;
	pthread_mutex_t	*lock_right;
	pthread_mutex_t	*lock_left;
	struct t_philo	*parent;
}					t_diner;

typedef struct s_philo
{
	t_diner	*diner;
	unsigned long	number_of_philosophers;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	number_of_times_each_philosopher_must_eat;
	unsigned long	number_of_forks;
	unsigned long	start_time;
}			t_philo;

#endif
