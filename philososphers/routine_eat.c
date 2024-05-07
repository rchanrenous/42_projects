/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 22:19:31 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/31 01:30:41 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_unlock_fork(t_philo *philo)
{
	if (philo->n == 1)
	{
		pthread_mutex_unlock(philo->f2);
		pthread_mutex_unlock(philo->f1);
	}
	else
	{
		pthread_mutex_unlock(philo->f1);
		pthread_mutex_unlock(philo->f2);
	}
}

static void	philo_update_nb_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->param->end));
	pthread_mutex_lock(&(philo->is_dead));
	(philo->eat)++;
	if (philo->param->nb_eat >= 0 && philo->eat >= philo->param->nb_eat)
		philo->ate_enough = 1;
	pthread_mutex_unlock(&(philo->is_dead));
	pthread_mutex_unlock(&(philo->param->end));
}

static void	philo_lock_fork(t_philo *philo, int f)
{
	if (f == f1)
	{
		if (philo->n == 1)
			pthread_mutex_lock(philo->f2);
		else
			pthread_mutex_lock(philo->f1);
	}
	else if (f == f2)
	{
		if (philo->n == 1)
			pthread_mutex_lock(philo->f1);
		else
			pthread_mutex_lock(philo->f2);
	}
}

int	routine_eat(t_philo *philo, t_ts *ts_now)
{
	philo_lock_fork(philo, f1);
	gettimeofday(ts_now, NULL);
	if (philo_log(philo, msg_fork, ts_now) == 0)
	{
		if (philo->n == 1)
			return (pthread_mutex_unlock(philo->f2), 0);
		else
			return (pthread_mutex_unlock(philo->f1), 0);
	}
	philo_lock_fork(philo, f2);
	if (philo_log(philo, msg_fork, ts_now) == 0)
		return (philo_unlock_fork(philo), 0);
	if (philo_log(philo, msg_eat, ts_now) == 0)
		return (philo_unlock_fork(philo), 0);
	philo_update_nb_eat(philo);
	gettimeofday(ts_now, NULL);
	while (time_diff(ts_now, &(philo->ts_eat)) < philo->param->t2eat)
	{
		if (philo_is_over(philo->param) == 1)
			return (philo_unlock_fork(philo), 0);
		usleep(USLEEP_WHILE);
		gettimeofday(ts_now, NULL);
	}
	return (philo_unlock_fork(philo), 1);
}
