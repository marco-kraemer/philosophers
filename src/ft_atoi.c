/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:35:37 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/08 13:44:36 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int		conversion(const char *nptr, int i, int value)
{
	while (nptr[i] > 47 && nptr[i] < 58)
	{
		value = value * 10 + (nptr[i] - '0');
		i++;
	}
	return (value);
}

int		ft_atoi(const char *nptr)
{
	size_t	i;
	size_t	j;
	size_t	value;

	j = 1;
	i = 0;
	value = 0;
	while (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\v'
			|| nptr[i] == '\t' || nptr[i] == '\r' || nptr[i] == '\f')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			j = j * (-1);
		i++;
	}
	return (conversion(nptr, i, value) * j);
}
