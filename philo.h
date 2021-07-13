/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:06:54 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/12 20:56:09 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_diner
{
	unsigned int	id;
	pthread_t		thread;
	_Bool			*fork_right;
	_Bool			*fork_left;
	pthread_mutex_t	*lock_right;
	pthread_mutex_t	*lock_left;
	unsigned long	time_to_alive;
	struct s_philo	*parent;
}					t_diner;

typedef struct s_philo
{
	t_diner			*diner;
	unsigned int	philosophers_counter;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned int	times_must_eat;
	unsigned int	chopsticks_counter;
	unsigned long	start_time;
	_Bool			philosopher_dead;
	_Bool			*forks;
	pthread_mutex_t	*locks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
}					t_philo;

void			*ft_calloc(size_t count, size_t size);
int				error(char *msg);
t_philo			*get_args(int argc, char **argv);
t_diner			*diner_create(t_philo *philo);
void			assign_chopsticks(unsigned pos, unsigned counter,
					t_diner *diner, _Bool *forks);
void			assign_locks(unsigned pos, unsigned counter,
					t_diner *diner, pthread_mutex_t *locks);
int				mutex_init_loop(t_philo *philo);
void			mutex_destroy_loop(t_philo *philo);
int				thread_create_loop(t_diner *diner, t_philo *philo);
void			thread_join_loop(t_diner *diner);
unsigned long	get_time(void);
unsigned int	get_msec_since_start(unsigned long start_time);
void			*diner_life_loop(void *arg);

#endif
