/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:22:27 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/13 09:49:19 by maraurel         ###   ########.fr       */
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
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef	struct s_data {
	int	philosopher;

	int	num_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_must_eat;
	int	counter;

	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;

	pthread_mutex_t	*state;
	pthread_mutex_t	*meals;

	long	last_time_eat;
	long	start_time;
}		t_data;

int		ft_atoi(const char *nptr);

void	wait(int length);
long	get_time(void);

void	*start_simulation(void *arg);
void	*check_meals(void *ptr);
void	*check_death(void *ptr);

#endif
