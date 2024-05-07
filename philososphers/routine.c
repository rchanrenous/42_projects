/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 18:09:19 by rchan--r          #+#    #+#             */
/*   Updated: 2024/05/06 15:19:41 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	routine_sleep(t_philo *philo, t_ts *ts_now, t_ts *ts_end_eat)
{
	gettimeofday(ts_now, NULL);
	if (philo_log(philo, msg_sleep, ts_now) == 0)
		return (0);
	gettimeofday(ts_end_eat, NULL);
	gettimeofday(ts_now, NULL);
	while (time_diff(ts_now, ts_end_eat) < philo->param->t2sleep)
	{
		if (philo_is_over(philo->param) == 1)
			return (0);
		usleep(USLEEP_WHILE);
		gettimeofday(ts_now, NULL);
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_ts	ts_now;
	t_ts	ts_end_eat;

	philo = (t_philo *)arg;
	if (philo->n % 2 == 0)
		usleep(USLEEP_DECALE);
	while (philo_is_over(philo->param) == 0)
	{
		if (routine_eat(philo, &ts_now) == 0)
			return (NULL);
		if (routine_sleep(philo, &ts_now, &ts_end_eat) == 0)
			return (NULL);
		gettimeofday(&ts_now, NULL);
		if (philo_log(philo, msg_think, &ts_now) == 0)
			return (NULL);
	}
	return (NULL);
}
