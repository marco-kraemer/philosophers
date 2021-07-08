/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 08:26:40 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/08 14:16:42 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_values(char **argv, t_data *data)
{
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

	data = *(t_data *)arg;
	printf("Incio: \n");
	usleep(100);
	printf("%i\n", data.num_philosophers);
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
