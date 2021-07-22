/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:06:54 by tsierra-          #+#    #+#             */
/*   Updated: 2021/07/22 20:00:02 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_diner
{
	unsigned int	id;
	unsigned int	times_eat;
	pthread_t		thread;
	_Bool			*chip;
	_Bool			*fork_right;
	_Bool			*fork_left;
	pthread_mutex_t	*lock_right;
	pthread_mutex_t	*lock_left;
	pthread_mutex_t	eat_mutex;
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
	unsigned int	eat_done;
	_Bool			philosopher_dead;
	_Bool			*chips;
	_Bool			*forks;
	pthread_mutex_t	*locks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	eat_mutex;
}					t_philo;

void			*ft_calloc(size_t count, size_t size);
int				ft_strneg(const char *s);
int				ft_strdigit(char *str);
int				ft_isdigit(int c);
size_t			ft_strlen(const char *s);
int				ft_atoi(const char *str);
int				error(char *msg);
void			init_chips(t_diner *diner, t_philo *philo);
t_philo			*create_philo(int argc, char **argv);
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
void			dsleep(unsigned int time_to_sleep);
void			print_status(t_diner *diner, char *status);
int				set_chopsticks(t_diner *diner, _Bool value);
void			give_chip_to_right(t_diner *diner);
int				hold_chopsticks(t_diner *diner);
void			set_dead(t_diner *diner, char *str);
void			sleeping(t_diner *diner);
int				eating(t_diner *diner);
int				count_eat(t_diner *diner);
void			init_chips(t_diner *diner, t_philo *philo);
void			*diner_life_loop(void *arg);
void			philo_free(t_philo **philo, t_diner **diner);

#endif
