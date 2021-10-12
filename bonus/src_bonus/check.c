/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 08:21:43 by maraurel          #+#    #+#             */
/*   Updated: 2021/10/12 09:50:35 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*check_meals(void *ptr)
{
	t_data	*data;
	int		i;

	data = (t_data *)ptr;
	i = 0;
	while (i < data->num_philosophers)
	{
		sem_wait(data->meals);
		i++;
	}
	i = 0;
	while (i < data->num_philosophers)
	{
		kill(data->pids[i], 15);
		i++;
	}
	sem_unlink(SEM_NAME);
	sem_unlink(SEM_NAME2);
	*(data->check_end) = 1;
	return (ptr);
}

void	*check_death(void *ptr)
{
	t_data	*data;
	int		i;

	i = -1;
	data = (t_data *)ptr;
	while (TRUE)
	{
		if (get_time() - data->last_time_eat > data->time_to_die)
		{
			printf("%ld %i died\n", (get_time() - data->start_time),
				data->philosopher);
			*(data->check_end) = 1;
			while (++i < data->num_philosophers)
				sem_post(data->meals);
			return (NULL);
		}
		else if (data->time_must_eat != -1
			&& data->counter >= data->time_must_eat)
		{
			data->check_end_meals++;
			sem_post(data->meals);
			return (NULL);
		}
	}
	return (NULL);
}
