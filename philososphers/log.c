/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:59:59 by rchan--r          #+#    #+#             */
/*   Updated: 2024/05/06 16:29:23 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_update_last_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->is_dead));
	gettimeofday(&(philo->ts_eat), NULL);
	pthread_mutex_unlock(&(philo->is_dead));
}

int	philo_log(t_philo *philo, int msg, t_ts *ts_now)
{
	long long int	time;

	pthread_mutex_lock(&(philo->param->end));
	if (philo->param->finished == 1)
		return (pthread_mutex_unlock(&(philo->param->end)), 0);
	pthread_mutex_lock(&(philo->is_dead));
	gettimeofday(ts_now, NULL);
	time = time_diff(ts_now, &(philo->param->ts_start));
	if (time_diff(ts_now, &(philo->ts_eat)) > philo->param->t2die)
		return (philo_log_unlock(philo), 0);
	if (msg == msg_fork)
		//printf("\033[1;33m%6lld %3d has taken a fork\n", time, philo->n);
		printf("\033[1;33m%lld %d has taken a fork\n", time, philo->n);
	else if (msg == msg_eat)
	{
		//printf("\033[1;32m%6lld %3d is eating\n", time, philo->n);
		printf("\033[1;32m%lld %d is eating\n", time, philo->n);
		gettimeofday(&(philo->ts_eat), NULL);
	}
	else if (msg == msg_sleep)
		//printf("\033[1;34m%6lld %3d is sleeping\n", time, philo->n);
		printf("\033[1;34m%lld %d is sleeping\n", time, philo->n);
	else if (msg == msg_think)
		//printf("\033[1;37m%6lld %3d is thinking\n", time, philo->n);
		printf("\033[1;37m%lld %d is thinking\n", time, philo->n);
	printf("\033[0m");
	philo_log_unlock(philo);
	return (1);
}
