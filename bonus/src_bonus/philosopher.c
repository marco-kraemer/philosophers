/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 11:03:57 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/13 11:12:33 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	get_time(void)
{
	struct timeval	current;

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

void	*check_meals(void *ptr)
{
	t_data	*data;
	int		i;

	data = (t_data *)ptr;
	i = 0;
	if (data->time_must_eat != 0)
		pthread_mutex_lock(data->meals);
	while (data->time_must_eat != 0 && i < data->num_philosophers)
	{
		pthread_mutex_lock(data->meals);
		i++;
	}
	printf("Nobody is dead!\n");
	pthread_mutex_unlock(data->state);
	return (NULL);
}

void	*check_death(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	while (TRUE)
	{
		if (get_time() - data->last_time_eat > data->time_to_die)
		{
			printf("%ld %i died\n", (get_time() - data->start_time),
				data->philosopher);
			pthread_mutex_unlock(data->state);
			return (NULL);
		}
		else if (data->time_must_eat != -1
			&& data->counter >= data->time_must_eat)
		{
			wait((float)data->philosopher);
			pthread_mutex_unlock(data->meals);
			return (NULL);
		}
	}
	return (NULL);
}

void	printf_message(int rule, t_data *data)
{
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

void	*start_simulation(void *arg)
{
	t_data			*data;
	pthread_t		th;

	data = (t_data *)arg;
	pthread_create(&th, NULL, check_death, data);
	if ((data->philosopher % 2) == 0)
		wait(((float)data->time_to_eat) * 0.9 + 1);
	while (TRUE)
	{
		pthread_mutex_lock(&data->right_fork);
		printf_message(0, data);
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
	return (arg);
}


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
