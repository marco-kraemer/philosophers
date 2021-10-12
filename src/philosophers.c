/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 08:26:40 by maraurel          #+#    #+#             */
/*   Updated: 2021/10/12 10:14:47 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	exit_threads(t_data *data, pthread_t th, pthread_mutex_t state)
{
	int	i;

	i = 0;
	while (i < data[0].num_philosophers)
		pthread_mutex_destroy(&data[i++].right_fork);
	pthread_mutex_destroy(&state);
	i = 0;
	while (i < data[0].num_philosophers)
	{
		pthread_join(data[i].th, NULL);
		i++;
	}
	if (data[0].time_must_eat != -1)
		pthread_join(th, NULL);
	free(data);
}

void	create_threads(t_data *data, int check_end, int check_end_meals)
{
	pthread_mutex_t		state;
	pthread_t			th;
	int					i;

	pthread_mutex_init(&state, NULL);
	pthread_mutex_lock(&state);
	i = 0;
	while (i < data[0].num_philosophers)
	{
		data[i].state = &state;
		data[i].check_end = &check_end;
		data[i].check_end_meals = &check_end_meals;
		pthread_create(&data[i].th, NULL, start_simulation, &data[i]);
		i++;
	}
	th = 0;
	if (data[0].time_must_eat != -1)
		pthread_create(&th, NULL, check_meals, &data[0]);
	pthread_mutex_lock(&state);
	exit_threads(data, th, state);
}

void	init_all(t_data *data, char **argv)
{
	int	i;

	i = 0;
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
}

int	check_error(char **argv, int argc)
{
	int	i;
	int	num;

	if (argc != 5 && argc != 6)
		return (1);
	i = 1;
	while (argv[i])
	{
		num = ft_atoi(argv[i]);
		if (num <= 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		*data;

	if (check_error(argv, argc) == 1)
		return (1);
	data = malloc(sizeof(t_data) * ft_atoi(argv[1]));
	init_all(data, argv);
	create_threads(data, 0, 0);
	return (0);
}
