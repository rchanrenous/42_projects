/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:57:50 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/30 23:09:41 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	threads_join(pthread_t *threads, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int	threads_run(t_philo **philos, t_param *param)
{
	pthread_t	*threads;
	t_ts		ts_now;
	int			i;

	threads = malloc(sizeof(pthread_t) * param->nb_philo);
	if (threads == NULL)
		return (0);
	i = 0;
	gettimeofday(&(param->ts_start), NULL);
	while (i < param->nb_philo)
	{
		gettimeofday(&(philos[i]->ts_eat), NULL);
		if (pthread_create(threads + i, NULL, &routine, philos[i]) != 0)
			return (free(threads), 0);
		i++;
	}
	i = 0;
	while (philo_is_over(param) == 0)
	{
		philos_check(philos, param, &ts_now, &i);
		usleep(USLEEP_WHILE);
		i = 0;
	}
	threads_join(threads, param->nb_philo);
	return (free(threads), 1);
}
