/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 11:03:57 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/13 12:14:02 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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

void	start_simulation(t_data data, sem_t semaphore)
{
	sem_wait(&semaphore);
	printf("Process number %i entered semaphore\n", data.philosopher);
	sleep(1);
	printf("Process number %i exited semaphore\n", data.philosopher);
	sem_post(&semaphore);
}

void	create_process(t_data *data)
{
	int	i;
	pid_t	pid;
	sem_t	*semaphore;
	
	i = 0;
	semaphore = sem_open("semaphore", O_CREAT, 777, 2);
	while (i < data[0].num_philosophers)
	{
		pid = fork();
		if (pid == 0)
		{
			start_simulation(data[i], *semaphore);
			exit(0);
		}
		i++;
	}
	i = 0;
	while (i < data[0].num_philosophers)
	{
		wait(NULL);
		i++;
	}
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
		data[i].start_time = get_time();
		data[i].philosopher = i + 1;
		data[i].last_time_eat = data[i].start_time;
		data[i++].counter = 0;
	}
	create_process(data);
}
