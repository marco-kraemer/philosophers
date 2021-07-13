/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 08:26:40 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/13 10:00:35 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	create_threads(t_data *data)
{
	int					i;
	pthread_t			th;
	pthread_mutex_t		state;
	pthread_mutex_t		meals;

	pthread_mutex_init(&state, NULL);
	pthread_mutex_init(&meals, NULL);
	pthread_mutex_lock(&state);
	i = 0;
	while (i < data[0].num_philosophers)
	{
		data[i].state = &state;
		data[i].meals = &meals;
		pthread_create(&th, NULL, start_simulation, &data[i]);
		i++;
	}
	if (data[0].time_must_eat != -1)
		pthread_create(&th, NULL, check_meals, &data[0]);
	pthread_mutex_lock(&state);
	i = 0;
	while (i < data[0].num_philosophers)
		pthread_mutex_destroy(&data[i++].right_fork);
	pthread_mutex_destroy(&state);
	pthread_mutex_destroy(&meals);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data		*data;
	static int	i;

	if (argc != 5 && argc != 6)
		return (1);
	data = malloc(sizeof(t_data) * ft_atoi(argv[1]));
	while (i < ft_atoi(argv[1]))
	{
		data[i].num_philosophers = ft_atoi(argv[1]);
		data[i].time_to_die = ft_atoi(argv[2]);
		data[i].time_to_eat = ft_atoi(argv[3]);
		data[i].time_to_sleep = ft_atoi(argv[4]);
		data[i].time_must_eat = -1;
		if (argv[5])
			data[i].time_must_eat = ft_atoi(argv[5]);
		pthread_mutex_init(&data[i].right_fork, NULL);
		if (i != 0)
			data[i].left_fork = &data[i - 1].right_fork;
		data[i].start_time = get_time();
		data[i].philosopher = i + 1;
		data[i].last_time_eat = data[i].start_time;
		data[i++].counter = 0;
	}
	data[0].left_fork = &data[data[0].num_philosophers - 1].right_fork;
	create_threads(data);
}
