/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 08:21:43 by maraurel          #+#    #+#             */
/*   Updated: 2021/10/10 13:33:25 by maraurel         ###   ########.fr       */
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
	printf("All philosophers ate at least %i times!\n", data->time_must_eat);
	free(data->pids);
	sem_unlink(SEM_NAME);
	sem_unlink(SEM_NAME2);
	exit(0);
	return (ptr);
}

void	*check_death(void *ptr)
{
	t_data	*data;
	int		check;

	data = (t_data *)ptr;
	check = 1;
	while (TRUE)
	{
		if (get_time() - data->last_time_eat > data->time_to_die)
		{
			printf("%ld %i died\n", (get_time() - data->start_time),
				data->philosopher);
			exit(0);
		}
		else if (data->time_must_eat != -1
			&& data->counter >= data->time_must_eat && check)
		{
			sem_post(data->meals);
			check = 0;
			return (NULL);
		}
	}
	return (NULL);
}
