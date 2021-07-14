/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 11:03:57 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/14 15:39:03 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#define	SEM_NAME "as"

long	get_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (TIME_MS);
}

void	ft_wait(int length)
{
	long	time;

	time = get_time();
	while (get_time() < time + length)
		usleep(length);
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
			exit(0);
		}
		else if (data->time_must_eat != -1
			&& data->counter >= data->time_must_eat)
		{
			ft_wait((float)data->philosopher);
			exit (0);
		}
	}
	return (NULL);
}

void	start_simulation(t_data *data)
{
	sem_t *semaphore;
	pthread_t	th;

	semaphore = sem_open(SEM_NAME, O_RDWR);
	pthread_create(&th, NULL, check_death, data);
	if ((data->philosopher % 2) == 0)
		ft_wait(data->time_to_eat + 0.0001);
	while (TRUE)
	{
		sem_wait(semaphore);
		printf_message(0, data);
		sem_wait(semaphore);
		printf_message(0, data);
		data->last_time_eat = get_time();
		printf_message(1, data);
		ft_wait(data->time_to_eat);
		sem_post(semaphore);
		sem_post(semaphore);
		data->counter += 1;
		printf_message(2, data);
		ft_wait(data->time_to_sleep);
		printf_message(3, data);
	}
	sem_close(semaphore);
}

void	create_process(t_data *data)
{
	sem_t *semaphore;
	pid_t pids[data[0].num_philosophers];
	int	 i;

	semaphore = sem_open(SEM_NAME, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, data[0].num_forks);
	sem_close(semaphore);
	i = 0;
	while (i < data[0].num_philosophers)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			start_simulation(&data[i]);
		i++;
	}
	i = 0;
	waitpid(-1, NULL, 0);
	sem_unlink(SEM_NAME);
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
		data[i].num_forks = ft_atoi(argv[1]);
		data[i].time_to_die = ft_atoi(argv[2]);
		data[i].time_to_eat = ft_atoi(argv[3]);
		data[i].time_to_sleep = ft_atoi(argv[4]);
		data[i].time_must_eat = -1;
		if (argv[5])
			data[i].time_must_eat = ft_atoi(argv[5]);
		data[i].start_time = get_time();
		data[i].philosopher = i + 1;
		data[i].last_time_eat = data[i].start_time;
		data[i++].counter = 0;
	}
	create_process(data);
}
