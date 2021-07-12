/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 08:26:40 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/12 14:24:54 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"


long	get_time(void)
{
	struct timeval current;

	gettimeofday(&current, NULL);
	return (TIME_MS);
}

void	wait(int length)
{
	long	time;

	time = get_time();
	while (get_time() < time + length)
		usleep(length);
}

void	*start_simulation(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if ((data->philosopher % 2) == 0)
		wait(((float)data->time_to_eat));
	while (TRUE)
	{
		pthread_mutex_lock(&data->right_fork);
		printf("%ld %i has taken a fork\n", ( get_time() - data->start_time), data->philosopher);
		pthread_mutex_lock(data->left_fork);
		printf("%ld %i has taken a fork\n", ( get_time() - data->start_time), data->philosopher);
		printf("%ld %i is eating\n", ( get_time() - data->start_time), data->philosopher);
		wait(data->time_to_eat);
		pthread_mutex_unlock(data->left_fork);
		pthread_mutex_unlock(&data->right_fork);
		printf("%ld %i is sleeping\n", ( get_time() - data->start_time), data->philosopher);
		wait(data->time_to_sleep);
		printf("%ld %i is thinking\n", ( get_time() - data->start_time), data->philosopher);
	}
	return (arg);
}

void	create_threads(t_data *data)
{
	int	i;
	pthread_t	th;
	pthread_mutex_t	state;
	pthread_mutex_t	meals;

	i = 0;
	while (i < data[0].num_philosophers)
	{
		pthread_create(&th, NULL, start_simulation, &data[i]);
		i++;
	}
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
	t_data	*data;
	int 	i;

	if (argc != 5 && argc != 6)
		return (1);
	if (!(data = malloc(sizeof(t_data) * ft_atoi(argv[1]))))
		return (1);
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		data[i].num_philosophers = ft_atoi(argv[1]);
		data[i].time_to_die = ft_atoi(argv[2]);
		data[i].time_to_eat = ft_atoi(argv[3]);
		data[i].time_to_sleep = ft_atoi(argv[4]);
		if (argv[4])
			data[i].time_must_eat = ft_atoi(argv[5]);
		else
			data[i].time_must_eat = 0;
		pthread_mutex_init(&data[i].right_fork, NULL);
		if (i != 0)
			data[i].left_fork = &data[i - 1].right_fork;
		data[i].start_time = get_time();
		data[i].philosopher = i + 1;
		i++;
	}
	data[0].left_fork = &data[data[0].num_philosophers - 1].right_fork;
	create_threads(data);
}
