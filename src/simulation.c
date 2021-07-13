/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 09:47:01 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/13 09:47:43 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*start_simulation(void *arg)
{
	t_data			*data;
	pthread_t		th;

	data = (t_data *)arg;
	pthread_create(&th, NULL, check_death, data);
	if ((data->philosopher % 2) == 0)
		wait(((float)data->time_to_eat) * 0.9 + 1);
	while (TRUE)
	{
		pthread_mutex_lock(&data->right_fork);
		printf("%ld %i has taken a fork\n", (get_time() - data->start_time),
			data->philosopher);
		pthread_mutex_lock(data->left_fork);
		printf("%ld %i has taken a fork\n", (get_time() - data->start_time),
			data->philosopher);
		data->last_time_eat = get_time();
		printf("%ld %i is eating\n", (get_time() - data->start_time),
			data->philosopher);
		wait(data->time_to_eat);
		pthread_mutex_unlock(data->left_fork);
		pthread_mutex_unlock(&data->right_fork);
		data->counter += 1;
		printf("%ld %i is sleeping\n", (get_time() - data->start_time),
			data->philosopher);
		wait(data->time_to_sleep);
		printf("%ld %i is thinking\n", (get_time() - data->start_time),
			data->philosopher);
	}
	return (arg);
}
