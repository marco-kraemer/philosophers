/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 11:03:57 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/14 09:26:31 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#define	SEM_NAME "sem"

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

void	start_simulation(t_data data)
{
	sem_t *semaphore;

	semaphore = sem_open(SEM_NAME, O_RDWR);
	sem_wait(semaphore);
	printf("PID %ld PHILOSOPHER: %i acquired semaphore\n", (long) getpid(), data.philosopher);
	sleep(1);
	sem_post(semaphore);
	printf("PID %ld PHILOSOPHER: %i exited semaphore\n", (long) getpid(), data.philosopher);
	sem_close(semaphore);
}

void	create_process(t_data *data)
{
	sem_t *semaphore;
	pid_t pids[data[0].num_philosophers];
	int	 i;

	semaphore = sem_open(SEM_NAME, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 1);
	sem_close(semaphore);
	i = 0;
	while (i < data[0].num_philosophers)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			start_simulation(data[i]);
		i++;
	}
	i = 0;
	while (i < data[0].num_philosophers)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
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
