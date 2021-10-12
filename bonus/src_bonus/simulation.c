/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 08:23:16 by maraurel          #+#    #+#             */
/*   Updated: 2021/10/12 09:55:52 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	printf_message(int rule, t_data data)
{
	if (*(data.check_end) == 1)
		return ;
	if (rule == 0)
		printf("%ld %i has taken a fork\n", (get_time() - data.start_time),
			data.philosopher);
	else if (rule == 1)
		printf("%ld %i is eating\n", (get_time() - data.start_time),
			data.philosopher);
	else if (rule == 2)
		printf("%ld %i is sleeping\n", (get_time() - data.start_time),
			data.philosopher);
	else
		printf("%ld %i is thinking\n", (get_time() - data.start_time),
			data.philosopher);
}

void	routine(t_data data)
{
	pthread_t	th;

	pthread_create(&th, NULL, check_death, &data);
	while (*(data.check_end) == 0)
	{
		if (data.check_end_meals == data.time_must_eat)
			break ;
		sem_wait(data.forks);
		printf_message(0, data);
		sem_wait(data.forks);
		printf_message(0, data);
		data.last_time_eat = get_time();
		printf_message(1, data);
		ft_wait(data.time_to_eat);
		sem_post(data.forks);
		sem_post(data.forks);
		data.counter += 1;
		printf_message(2, data);
		ft_wait(data.time_to_sleep);
		printf_message(3, data);
	}
	pthread_join(th, NULL);
}

void	start_simulation(t_data data)
{
	data.check_end_meals = 0;
	if ((data.philosopher % 2) == 0)
		ft_wait(data.time_to_eat + 0.0001);
	routine(data);
	sem_close(data.forks);
}
