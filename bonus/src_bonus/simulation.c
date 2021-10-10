/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 08:23:16 by maraurel          #+#    #+#             */
/*   Updated: 2021/10/10 13:33:12 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	printf_message(int rule, t_data data)
{
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

void	start_simulation(t_data data)
{
	sem_t		*semaphore;
	pthread_t	th;

	semaphore = sem_open(SEM_NAME, O_RDWR);
	pthread_create(&th, NULL, check_death, &data);
	if ((data.philosopher % 2) == 0)
		ft_wait(data.time_to_eat + 0.0001);
	while (TRUE)
	{
		sem_wait(semaphore);
		printf_message(0, data);
		sem_wait(semaphore);
		printf_message(0, data);
		data.last_time_eat = get_time();
		printf_message(1, data);
		ft_wait(data.time_to_eat);
		sem_post(semaphore);
		sem_post(semaphore);
		data.counter += 1;
		printf_message(2, data);
		ft_wait(data.time_to_sleep);
		printf_message(3, data);
	}
	sem_close(semaphore);
}
