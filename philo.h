#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_philo
{
	pthread_mutex_t	lock;
	int		id;
}	t_philo;

#endif
