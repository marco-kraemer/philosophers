/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 09:48:17 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/13 09:48:25 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	get_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (TIME_MS);
}

void	wait(int length)
{
	long	time;

	time = get_time();
	while (get_time() < time + length)
		usleep(length);
}
