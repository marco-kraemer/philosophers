/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 08:26:40 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/08 15:41:56 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_values(char **argv, t_data *data)
{
	struct timeval start;

	gettimeofday(&start, NULL);
	data->start_usec = start.tv_usec;
	data->start_sec = start.tv_sec;
	data->num_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[4])
		data->time_must_eat = ft_atoi(argv[5]);
	else
		data->time_must_eat = 0;
}

void	*start_simulation(void *arg)
{
	t_data	data;
	struct timeval current;

	data = *(t_data *)arg;
	usleep(20 * USEC_TO_MS);
	gettimeofday(&current, NULL);
	data.current_sec = current.tv_sec;
	data.current_usec = current.tv_usec;
	printf("TIME: %ld\n", TIME_MS);
	return (arg);
}

void	create_threads(t_data data)
{
	int	i;
	pthread_t	ph[data.num_philosophers];

	i = 0;
	while (i < data.num_philosophers)
	{
		pthread_create(&ph[i], NULL, &start_simulation, &data);
		i++;
	}
	i = 0;
	while (i < data.num_philosophers)
	{
		pthread_join(ph[i], NULL);
		i++;
	}		
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("Incorrect number of arguments\n");
		exit(EXIT_FAILURE);
	}
	init_values(argv, &data);
	create_threads(data);
}
