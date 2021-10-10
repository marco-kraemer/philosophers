/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 11:03:57 by maraurel          #+#    #+#             */
/*   Updated: 2021/10/10 13:33:21 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	create_process(t_data data)
{
	int			i;
	pid_t	pid;

	data.pids = malloc(sizeof(pid_t) * data.num_philosophers);
	i = 0;
	if (data.time_must_eat != -1)
	{
		pid = fork();
		if (pid == 0)
			check_meals((void *) &data);
	}
	while (i < data.num_philosophers)
	{
		data.pids[i] = fork();
		if (data.pids[i] == 0)
		{
			data.philosopher = i + 1;
			start_simulation(data);
		}
		i++;
	}
	waitpid(-1, NULL, 0);
	i = 0;
	while (i < data.num_philosophers)
		kill(data.pids[i++], SIGTERM);
	sem_close(data.meals);
	sem_unlink(SEM_NAME);
	sem_unlink(SEM_NAME2);
}

int	main(int argc, char **argv)
{
	t_data		data;
	static int	i;
	sem_t		*semaphore;

	if (argc != 5 && argc != 6)
		return (1);
	data.num_philosophers = ft_atoi(argv[1]);
	data.num_forks = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	data.time_must_eat = -1;
	if (argv[5])
		data.time_must_eat = ft_atoi(argv[5]);
	data.start_time = get_time();
	data.philosopher = i + 1;
	data.last_time_eat = data.start_time;
	data.counter = 0;
	semaphore = sem_open(SEM_NAME, O_CREAT | O_EXCL,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, data.num_forks);
	sem_close(semaphore);
	data.meals = sem_open(SEM_NAME2, O_CREAT | O_EXCL,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 0);
	create_process(data);
}
