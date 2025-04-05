/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:18:53 by mnazar            #+#    #+#             */
/*   Updated: 2025/04/04 01:18:53 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	ft_convert(char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (*str >= 9 && *str <= 13)
		str++;
	while (str[i])
		i++;
	if (i > 9)
		return (LLONG_MAX);
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result);
}

int	init_data(t_data *data, char **argv)
{
	data->num_philos = ft_convert(argv[1]);
	data->time_to_die = ft_convert(argv[2]);
	data->time_to_eat = ft_convert(argv[3]);
	data->time_to_sleep = ft_convert(argv[4]);
	if (argv[5])
		data->must_eat = ft_convert(argv[5]);
	else
		data->must_eat = -1;
	if (data->num_philos >= INT_MAX || data->time_to_die >= INT_MAX
		|| data->time_to_eat >= INT_MAX || data->time_to_sleep >= INT_MAX
		|| data->must_eat >= INT_MAX)
		return (printf("Error: Incorrect arguments given\n"), 1);
	data->forks = malloc(sizeof(int) * data->num_philos);
	if (!data->forks)
		return (printf("Error: Malloc failed\n"), 1);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (free(data->forks), printf("Error: Malloc failed\n"), 1);
	init_forks(data);
	data->death = false;
	return (0);
}

int	init_philos(t_data *data)
{
	unsigned long long	i;

	i = 0;
	data->start_time = get_time();
	if (data->start_time == -1)
		return (1);
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_philos;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

void	init_forks(t_data *data)
{
	unsigned long long	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (i == 0 || i == data->num_philos - 1)
			data->forks[i] = data->num_philos;
		else if (i % 2 == 0)
			data->forks[i] = i + 2;
		else
			data->forks[i] = i + 1;
		i++;
	}
}

int	init_mutex(t_data *data)
{
	unsigned long long	i;

	i = 0;
	data->forks_mutex = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks_mutex)
		return (printf("Error: Malloc failed\n"), 1);
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->eat_mutex, NULL);
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	return (0);
}
