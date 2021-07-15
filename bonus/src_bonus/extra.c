/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 08:22:54 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/15 08:23:04 by maraurel         ###   ########.fr       */
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
