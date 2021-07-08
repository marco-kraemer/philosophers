/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 08:26:40 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/08 13:48:59 by maraurel         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("Incorrect number of arguments\n");
		exit(EXIT_FAILURE);
	}
	init_values(argv, &data);
	printf("%i\n", data.time_to_die);
}
