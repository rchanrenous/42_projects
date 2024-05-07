/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:05:28 by rchan--r          #+#    #+#             */
/*   Updated: 2024/05/06 16:31:30 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_log_unlock(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->is_dead));
	pthread_mutex_unlock(&(philo->param->end));
}

int	philo_is_dead(t_philo *philo, t_ts *ts_now, int *nb_enough)
{
	long long int	time;

	pthread_mutex_lock(&(philo->param->end));
	pthread_mutex_lock(&(philo->is_dead));
	gettimeofday(ts_now, NULL);
	if (time_diff(ts_now, &(philo->ts_eat)) > philo->param->t2die)
	{
		philo->param->finished = 1;
		time = time_diff(ts_now, &(philo->param->ts_start));
		//printf("\033[1;31m%6lld %3d died\033[0m\n", time, philo->n);
		printf("\033[1;31m%lld %d died\033[0m\n", time, philo->n);
		return (philo_log_unlock(philo), 1);
	}
	if (philo->ate_enough == 1)
		(*nb_enough)++;
	if (*nb_enough == philo->param->nb_philo)
	{
		philo->param->finished = 1;
		return (philo_log_unlock(philo), 1);
	}
	philo_log_unlock(philo);
	return (0);
}

void	philos_check(t_philo **philos, t_param *p, t_ts *ts_now, int *enough)
{
	int	i;

	i = 0;
	while (i < p->nb_philo)
	{
		if (philo_is_dead(philos[i], ts_now, enough) == 1)
			return ;
		i++;
	}
}

int	philo_is_over(t_param *param)
{
	pthread_mutex_lock(&(param->end));
	if (param->finished == 1)
	{
		pthread_mutex_unlock(&(param->end));
		return (1);
	}
	pthread_mutex_unlock(&(param->end));
	return (0);
}
