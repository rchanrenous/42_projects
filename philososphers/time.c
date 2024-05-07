/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:42:04 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/30 22:56:21 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_ms(struct timeval *ts)
{
	long long	res;

	res = ((long long)ts->tv_sec * 1000) + ((long long)ts->tv_usec / 1000);
	return (res);
}

long long	time_diff(struct timeval *ts1, struct timeval *ts2)
{
	struct timeval	res;
	int				neg;

	neg = 0;
	if (ts1->tv_usec < ts2->tv_usec)
	{
		neg = 1;
		res.tv_usec = ts1->tv_usec + 1000000 - ts2->tv_usec;
	}
	else
		res.tv_usec = ts1->tv_usec - ts2->tv_usec;
	res.tv_sec = ts1->tv_sec - ts2->tv_sec - neg;
	return (time_ms(&res));
}
