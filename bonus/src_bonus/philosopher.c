/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 11:03:57 by maraurel          #+#    #+#             */
/*   Updated: 2021/10/12 09:50:08 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	exit_program(t_data *data, pthread_t th)
{
	int	i;
	int	ret;

	i = 0;
	while (i < data->num_philosophers)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = 0;
			while (i < data->num_philosophers)
			{
				kill(data->pids[i], 15);
				i++;
			}
			break ;
		}
		i++;
	}
	pthread_join(th, NULL);
	free(data->pids);
	sem_close(data->meals);
	sem_close(data->forks);
	sem_unlink(SEM_NAME);
	sem_unlink(SEM_NAME2);
}

void	create_process(t_data *data)
{
	int			i;
	int			check;
	pthread_t	th;

	check = 0;
	data->check_end = &check;
	data->pids = malloc(sizeof(pid_t) * data->num_philosophers);
	i = 0;
	while (i < data->num_philosophers)
	{
		data->pids[i] = fork();
		if (data->pids[i] == 0)
		{
			data->philosopher = i + 1;
			start_simulation(*data);
		}
		i++;
	}
	pthread_create(&th, NULL, check_meals, &data[0]);
	exit_program(data, th);
}

int	main(int argc, char **argv)
{
	t_data		data;
	static int	i;

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
	sem_unlink(SEM_NAME);
	sem_unlink(SEM_NAME2);
	data.forks = sem_open(SEM_NAME, O_CREAT, S_IRWXU, data.num_forks);
	data.meals = sem_open(SEM_NAME2, O_CREAT, S_IRWXU, 0);
	create_process(&data);
	return (0);
}
