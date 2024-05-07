/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:18:12 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/31 01:00:03 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

# define USLEEP_WHILE 10
# define USLEEP_DECALE 30000

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_ts;

enum	e_msg
{
	msg_fork = 0,
	msg_eat = 1,
	msg_sleep = 2,
	msg_think = 3
};

enum	e_fork
{
	f1,
	f2
};

typedef struct param
{
	int			nb_philo;
	long int	t2die;
	long int	t2eat;
	long int	t2sleep;
	int			nb_eat;
	int			finished;
	t_mutex		end;
	t_ts		ts_start;
}	t_param;

typedef struct philo
{
	t_param	*param;
	t_mutex	*f1;
	t_mutex	*f2;
	t_mutex	is_dead;
	t_ts	ts_eat;
	int		n;
	int		eat;
	int		ate_enough;
}	t_philo;

t_param		*read_input(int argc, char **argv);
t_philo		**init(t_mutex ***forks, t_param **param);
t_philo		**philos_init(t_param *t, t_mutex **f, int nb_philo);
void		philos_destroy(t_philo ***philos, int n);
t_mutex		**forks_init(int nb_philo);
void		forks_destroy(t_mutex ***forks, int n);

int			threads_run(t_philo **philos, t_param *param);

void		*routine(void *arg);
int			routine_eat(t_philo *philo, t_ts *ts);

void		philos_check(t_philo **phs, t_param *p, t_ts *ts_now, int *enough);
int			philo_is_over(t_param *param);
int			philo_log(t_philo *philo, int msg, t_ts *ts_now);
void		philo_log_unlock(t_philo *philo);

long long	time_diff(struct timeval *ts1, struct timeval *ts2);
long long	time_ms(struct timeval *ts);
#endif
