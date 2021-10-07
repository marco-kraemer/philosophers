/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 09:46:58 by maraurel          #+#    #+#             */
/*   Updated: 2021/10/07 16:12:12 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*check_meals(void *ptr)
{
	t_data	*data;
	int		i;

	data = (t_data *)ptr;
	i = 0;
	if (data->time_must_eat != 0)
		pthread_mutex_lock(data->meals);
	while (data->time_must_eat != 0 && i < data->num_philosophers)
	{
		pthread_mutex_lock(data->meals);
		i++;
	}
	printf("Nobody is dead!\n");
	pthread_mutex_unlock(data->state);
	return (NULL);
}

void	*check_death(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	while (TRUE)
	{
		if (get_time() - data->last_time_eat > data->time_to_die)
		{
			printf("%ld %i died\n", (get_time() - data->start_time),
				data->philosopher);
			data->check_end = 1;
			pthread_mutex_unlock(data->state);
			return (NULL);
		}
		else if (data->time_must_eat != -1
			&& data->counter >= data->time_must_eat)
		{
			wait((float)data->philosopher);
			pthread_mutex_unlock(data->meals);
			return (NULL);
		}
	}
	return (NULL);
}
