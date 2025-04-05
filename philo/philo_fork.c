/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:07:38 by mnazar            #+#    #+#             */
/*   Updated: 2025/04/04 01:07:38 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_order(t_philo *philo, int *first, int *second)
{
	if (philo->left_fork < philo->right_fork)
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
	else
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
}

int	fork_checkers(t_philo *philo, int first, int second)
{
	int	first_id;
	int	second_id;

	pthread_mutex_lock(&philo->data->forks_mutex[first]);
	first_id = philo->data->forks[first];
	pthread_mutex_unlock(&philo->data->forks_mutex[first]);
	pthread_mutex_lock(&philo->data->forks_mutex[second]);
	second_id = philo->data->forks[second];
	pthread_mutex_unlock(&philo->data->forks_mutex[second]);
	if (first_id != philo->id && second_id != philo->id)
		return (1);
	return (0);
}

void	lock_the_forks(t_philo *philo, int first, int second)
{
	fork_order(philo, &first, &second);
	pthread_mutex_lock(&philo->data->forks_mutex[first]);
	pthread_mutex_lock(&philo->data->forks_mutex[second]);
}

void	drop_forks(t_philo *philo, int first, int second)
{
	fork_order(philo, &first, &second);
	pthread_mutex_unlock(&philo->data->forks_mutex[first]);
	pthread_mutex_unlock(&philo->data->forks_mutex[second]);
}
