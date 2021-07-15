/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:22:27 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/15 11:26:24 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define USEC_TO_MS 1000
# define TRUE 1
# define FALSE 0
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data {
	int				num_philosophers;
	int				philosopher;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_must_eat;
	int				counter;

	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;

	pthread_mutex_t	*meals;
	pthread_mutex_t	*state;

	long			start_time;
	long			last_time_eat;
}		t_data;

int		ft_atoi(const char *nptr);

void	wait(int length);
long	get_time(void);

void	*start_simulation(void *arg);
void	*check_meals(void *ptr);
void	*check_death(void *ptr);

#endif
