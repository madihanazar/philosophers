/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:06:25 by mnazar            #+#    #+#             */
/*   Updated: 2025/04/01 21:06:25 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_philo *philo)
{
	philo_sleep(philo->data->time_to_die, philo);
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->data->death = true;
	pthread_mutex_unlock(&philo->data->death_mutex);
	print_status(philo->data, philo->id, DEAD);
}

int	check_deadlock(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->death_mutex);
	if (data->death == false)
		i = 0;
	else
		i = 1;
	pthread_mutex_unlock(&data->death_mutex);
	return (i);
}

int	print_status(t_data *data, int id, int status)
{
	pthread_mutex_lock(&data->print_lock);
	if (status == DEAD)
		printf("%llu %d died\n", get_time() - data->start_time, id);
	if (check_deadlock(data))
		return (pthread_mutex_unlock(&data->print_lock), 1);
	if (!check_deadlock(data))
	{
		printf("%llu %d ", get_time() - data->start_time, id);
		if (status == EAT)
			printf("is eating\n");
		else if (status == SLEEP)
			printf("is sleeping\n");
		else if (status == THINK)
			printf("is thinking\n");
		else if (status == FORK)
			printf("has taken a fork\n");
	}
	pthread_mutex_unlock(&data->print_lock);
	return (0);
}

void	*thread_cycle(void *arg)
{
	t_philo	*philo_thread;
	int		left_fork;
	int		right_fork;

	philo_thread = (t_philo *)arg;
	if (philo_thread->data->num_philos == 1)
	{
		one_philo(philo_thread);
		return (NULL);
	}
	while (!check_deadlock(philo_thread->data))
	{
		fork_order(philo_thread, &left_fork, &right_fork);
		if (fork_checkers(philo_thread, left_fork, right_fork))
		{
			lock_the_forks(philo_thread, left_fork, right_fork);
			if (eat(philo_thread) == 1)
				return (drop_forks(philo_thread, left_fork, right_fork), NULL);
			if (sleep_thread(philo_thread) == 1)
				return (NULL);
			if (think(philo_thread) == 1)
				return (NULL);
		}
	}
	return (NULL);
}

int	create_philo_thread(t_data *data)
{
	unsigned long long	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&thread_cycle, &data->philos[i]) != 0)
			return (printf("Error: pthread_create failed\n"), 1);
		i++;
	}
	if (data->num_philos > 1 && pthread_create(&data->watcher, NULL,
			&monitor_philo, data))
		return (printf("Error: pthread_create failed\n"), 1);
	if (data->num_philos > 1 && pthread_join(data->watcher, NULL))
		return (printf("Error: pthread_join failed\n"), 1);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (printf("Error: pthread_join failed\n"), 1);
		i++;
	}
	return (0);
}
