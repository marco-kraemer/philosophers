/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:22:27 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/14 15:03:20 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS
# define PHILOSOPHERS
# define TIME_MS current.tv_sec * 1000 + current.tv_usec / 1000
# define USEC_TO_MS 1000
# define TRUE 1
# define FALSE 0
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef	struct s_data {
	int	philosopher;

	int	num_philosophers;
	int	num_forks;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_must_eat;
	int	counter;

	long	last_time_eat;
	long	start_time;

	int	state;

}		t_data;

typedef	struct s_all {
	t_data	*multiple;
	t_data	*one;
}		t_all;

int		ft_atoi(const char *nptr);

#endif
