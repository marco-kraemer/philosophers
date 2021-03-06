/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 09:47:01 by maraurel          #+#    #+#             */
/*   Updated: 2021/10/08 12:31:12 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	printf_message(int rule, t_data *data)
{
	if (*data->check_end == 1)
		return ;
	else if (*data->check_end_meals >= data->num_philosophers
		&& data->time_must_eat != -1)
		return ;
	if (rule == 0)
		printf("%ld %i has taken a fork\n", (get_time() - data->start_time),
			data->philosopher);
	else if (rule == 1)
		printf("%ld %i is eating\n", (get_time() - data->start_time),
			data->philosopher);
	else if (rule == 2)
		printf("%ld %i is sleeping\n", (get_time() - data->start_time),
			data->philosopher);
	else
		printf("%ld %i is thinking\n", (get_time() - data->start_time),
			data->philosopher);
}

void	routine(t_data *data)
{
	while (*(data->check_end) == 0)
	{
		if (*data->check_end_meals >= data->num_philosophers
			&& data->time_must_eat != -1)
			break ;
		pthread_mutex_lock(&data->right_fork);
		printf_message(0, data);
		if (data->num_philosophers == 1)
			break ;
		pthread_mutex_lock(data->left_fork);
		printf_message(0, data);
		data->last_time_eat = get_time();
		printf_message(1, data);
		wait(data->time_to_eat);
		pthread_mutex_unlock(data->left_fork);
		pthread_mutex_unlock(&data->right_fork);
		data->counter += 1;
		printf_message(2, data);
		wait(data->time_to_sleep);
		printf_message(3, data);
	}
}

void	*start_simulation(void *arg)
{
	t_data			*data;
	pthread_t		th;

	data = (t_data *)arg;
	pthread_create(&th, NULL, check_death, data);
	if ((data->philosopher % 2) == 0)
		wait(((float)data->time_to_eat) * 0.9 + 1);
	routine(data);
	pthread_mutex_unlock(data->state);
	pthread_join(th, NULL);
	return (arg);
}
