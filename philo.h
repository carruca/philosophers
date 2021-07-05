#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_diner
{
	int				id;
	pthread_t		thread;
	int				*fork_right;
	int				*fork_left;
	pthread_mutex_t	*lock_right;
	pthread_mutex_t	*lock_left;
	struct t_philo	*parent;
}					t_diner;

typedef struct s_philo
{
	t_diner	*diner;
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_each_philosopher_must_eat;
	int		number_of_forks;
}			t_philo;

#endif
