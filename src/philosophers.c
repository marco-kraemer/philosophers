/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 08:26:40 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/12 09:19:30 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	get_current_time(t_data *data)
{
	struct timeval current;

	gettimeofday(&current, NULL);
	data->current_sec = current.tv_sec;
	data->current_usec = current.tv_usec;
}

void	*start_simulation(void *arg)
{
	t_data	data;
	static int 	philosopher;

	data = *(t_data *)arg;
		printf("oi\n");

//	while (TRUE)
//	{
		get_current_time(&data);
	//	if (TIME_MS < 3)
		printf("PHILOSPHER %i --> %ld\n", data.philosopher,TIME_MS);
//		usleep(1 * USEC_TO_MS);
//	}
	philosopher++;
	pthread_exit(NULL);
	return (arg);
}

void	create_threads(t_data *data)
{
	int	i;
	pthread_t	th;

	i = 0;
	while (i < data[0].num_philosophers)
	{
		data[i].philosopher = i;
		pthread_create(&th, NULL, start_simulation, &data[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int 	i;
	struct timeval start;

	if (argc != 5 && argc != 6)
	{
		printf("Incorrect number of arguments\n");
		exit(EXIT_FAILURE);
	}
	if (!(data = malloc(sizeof(t_data) * ft_atoi(argv[1]))))
		return (1);
	gettimeofday(&start, NULL);
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		data[i].start_usec = start.tv_usec;
		data[i].start_sec = start.tv_sec;
		data[i].num_philosophers = ft_atoi(argv[1]);
		data[i].time_to_die = ft_atoi(argv[2]);
		data[i].time_to_eat = ft_atoi(argv[3]);
		data[i].time_to_sleep = ft_atoi(argv[4]);
		if (argv[4])
			data[i].time_must_eat = ft_atoi(argv[5]);
		else
			data[i].time_must_eat = 0;
		i++;
	}
	create_threads(data);
}
