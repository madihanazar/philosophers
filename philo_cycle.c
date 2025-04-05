/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:03:42 by mnazar            #+#    #+#             */
/*   Updated: 2025/04/04 01:03:42 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo)
{
	int	first;
	int	second;

	fork_order(philo, &first, &second);
	if (print_status(philo->data, philo->id, FORK) == 1)
		return (1);
	if (print_status(philo->data, philo->id, FORK) == 1)
		return (1);
	if (print_status(philo->data, philo->id, EAT) == 1)
		return (1);
	if (philo_sleep(philo->data->time_to_eat, philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->data->eat_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->eat_mutex);
	philo->data->forks[philo->left_fork] = philo->id;
	philo->data->forks[philo->right_fork] = philo->id;
	drop_forks(philo, first, second);
	return (0);
}

int	sleep_thread(t_philo *philo)
{
	if (print_status(philo->data, philo->id, SLEEP) == 1)
		return (1);
	if (philo_sleep(philo->data->time_to_sleep, philo) == 1)
		return (1);
	return (0);
}

int	think(t_philo *philo)
{
	if (print_status(philo->data, philo->id, THINK) == 1)
		return (1);
	return (0);
}
