/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:22:27 by maraurel          #+#    #+#             */
/*   Updated: 2021/10/11 11:28:44 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <sys/wait.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define USEC_TO_MS 1000
# define TRUE 1
# define FALSE 0
# define SEM_NAME "/semname01"
# define SEM_NAME2 "/semname02"

typedef struct s_data {
	int		philosopher;

	int		num_philosophers;
	int		num_forks;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		time_must_eat;
	int		counter;

	long		last_time_eat;
	long		start_time;

	int		pid_num;

	int		*check_end;
	int		check_end_meals;

	sem_t		*meals;
	sem_t		*forks;
	pid_t	*	pids;
}		t_data;

int		ft_atoi(const char *nptr);
void	*check_meals(void *ptr);
void	*check_death(void *ptr);
long	get_time(void);
void	ft_wait(int length);
#endif
