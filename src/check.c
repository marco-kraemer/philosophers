/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 09:46:58 by maraurel          #+#    #+#             */
/*   Updated: 2021/10/08 12:22:26 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*check_meals(void *ptr)
{
	int		i;
	t_data	*data;

	data = (t_data *)ptr;
	i = 0;
	while (*data->check_end == 0
		&& *data->check_end_meals < data->num_philosophers)
		i++;
	if (*data->check_end_meals >= data->num_philosophers)
		printf("All philosophers ate at least %i times!\n", data->time_must_eat);
	pthread_mutex_unlock(data->state);
	return (NULL);
}

void	*check_death(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	while (*(data->check_end) == 0)
	{
		if (get_time() - data->last_time_eat > data->time_to_die)
		{
			printf("%ld %i died\n", (get_time() - data->start_time),
				data->philosopher);
			*data->check_end = 1;
			return (NULL);
		}
		if (data->time_must_eat != -1
			&& data->counter >= data->time_must_eat)
		{
			*data->check_end_meals += 1;
			return (NULL);
		}
	}
	return (NULL);
}
