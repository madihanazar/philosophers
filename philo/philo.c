/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnazar <mnazar@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:12:56 by mnazar            #+#    #+#             */
/*   Updated: 2025/04/01 14:12:56 by mnazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_data *data)
{
	unsigned long long	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&data->eat_mutex);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->death_mutex);
}

void	free_data(t_data *data, int i)
{
	free(data->forks);
	free(data->philos);
	if (i == 1)
	{
		destroy_mutex(data);
		free(data->forks_mutex);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (printf("Error: Number of arguments is wrong\n"), 1);
	if (check_args(argv))
		return (printf("Error: Incorrect arguments given\n"), 1);
	if (init_data(&data, argv))
		return (1);
	if (init_philos(&data))
		return (free_data(&data, 0), 1);
	if (init_mutex(&data))
		return (free_data(&data, 0), 1);
	if (create_philo_thread(&data))
		return (free_data(&data, 1), 1);
	free_data(&data, 1);
	return (0);
}
