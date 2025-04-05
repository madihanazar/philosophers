/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:35:26 by mnazar            #+#    #+#             */
/*   Updated: 2025/04/01 14:35:26 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>

# define EAT 0
# define SLEEP 1
# define THINK 2
# define FORK 3
# define DEAD 4

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	unsigned long long	last_meal_time;
	int					left_fork;
	int					right_fork;
	pthread_t			thread;
	struct s_data		*data;
}	t_philo;

typedef struct s_data
{
	unsigned long long				num_philos;
	unsigned long long				time_to_die;
	unsigned long long				time_to_eat;
	unsigned long long				time_to_sleep;
	long long						must_eat;
	int								*forks;
	long long						start_time;
	pthread_mutex_t					*forks_mutex;
	pthread_mutex_t					print_lock;
	pthread_mutex_t					death_mutex;
	pthread_mutex_t					eat_mutex;
	bool							death;
	pthread_t						watcher;
	t_philo							*philos;
}	t_data;

int					check_args(char **argv);
int					ft_isdigit(int c);
int					init_data(t_data *data, char **argv);
int					init_philos(t_data *data);
void				init_forks(t_data *data);
int					init_mutex(t_data *data);
void				free_data(t_data *data, int i);
void				destroy_mutex(t_data *data);
int					create_philo_thread(t_data *data);
void				*thread_cycle(void *arg);
int					print_status(t_data *data, int id, int status);
int					check_deadlock(t_data *data);
void				one_philo(t_philo *philo);
int					eat(t_philo *philo);
int					sleep_thread(t_philo *philo);
int					think(t_philo *philo);
void				fork_order(t_philo *philo, int *first, int *second);
int					fork_checkers(t_philo *philo, int first, int second);
void				lock_the_forks(t_philo *philo, int first, int second);
void				drop_forks(t_philo *philo, int first, int second);
unsigned long long	get_time(void);
unsigned long long	ft_convert(char *str);
int					check_eats(t_data *data);
void				finish_eating(t_data *data);
void				terminate_philo(t_data *data, unsigned long long i);
void				*monitor_philo(void *arg);
int					philo_sleep(unsigned long long time, t_philo *philo);

#endif