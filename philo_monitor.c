/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:12:46 by mnazar            #+#    #+#             */
/*   Updated: 2025/04/04 01:12:46 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eats(t_data *data)
{
	unsigned long	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].meals_eaten < (int)data->must_eat)
			return (0);
		i++;
	}
	return (1);
}

void	finish_eating(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->death = true;
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_unlock(&data->eat_mutex);
}

void	terminate_philo(t_data *data, unsigned long long i)
{
	pthread_mutex_lock(&data->death_mutex);
	data->death = true;
	pthread_mutex_unlock(&data->death_mutex);
	print_status(data, data->philos[i].id, DEAD);
	pthread_mutex_unlock(&data->eat_mutex);
}

void	*monitor_philo(void *arg)
{
	t_data				*data;
	unsigned int		i;

	data = (t_data *)arg;
	while (!check_deadlock(data))
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->eat_mutex);
			if (data->must_eat > 0 && check_eats(data))
			{
				finish_eating(data);
				return (NULL);
			}
			if (get_time() > data->philos[i].last_meal_time + data->time_to_die)
			{
				terminate_philo(data, i);
				return (NULL);
			}
			pthread_mutex_unlock(&data->eat_mutex);
			i++;
		}
	}
	return (NULL);
}

int	philo_sleep(unsigned long long time, t_philo *philo)
{
	unsigned long long	start;

	start = get_time();
	while (get_time() < (start + time))
	{
		if (check_deadlock(philo->data))
			return (1);
		usleep(500);
	}
	return (0);
}
