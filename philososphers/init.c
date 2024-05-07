/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:03:35 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/30 22:44:59 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_destroy(t_philo ***philos, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&((*philos)[i]->is_dead));
		free((*philos)[i]);
		(*philos)[i] = NULL;
		i++;
	}
	free(*philos);
	*philos = NULL;
}

static void	philo_init_fields(t_philo *philo)
{
	philo->eat = 0;
	philo->ate_enough = 0;
}

//t_philo	**philos_init(t_param *t, t_mutex **f, t_mutex *end, int nb_philo)
t_philo	**philos_init(t_param *p, t_mutex **f, int nb_philo)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo *) * nb_philo);
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < nb_philo)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (philos[i] == NULL)
			return (philos_destroy(&philos, i), NULL);
		if (i == 0)
			philos[0]->f1 = f[nb_philo - 1];
		else
			philos[i]->f1 = f[i - 1];
		philos[i]->f2 = f[i];
		philos[i]->param = p;
		philos[i]->n = i + 1;
		philo_init_fields(philos[i]);
		if (pthread_mutex_init(&(philos[i]->is_dead), NULL) != 0)
			return (philos_destroy(&philos, i + 1), NULL);
		i++;
	}
	return (philos);
}

t_philo	**init(t_mutex ***forks, t_param **p)
{
	t_philo	**philos;

	if (p == NULL || *p == NULL || forks == NULL)
		return (NULL);
	*forks = forks_init((*p)->nb_philo);
	if (*forks == NULL)
	{
		pthread_mutex_destroy(&((*p)->end));
		free(*p);
		*p = NULL;
		return (NULL);
	}
	philos = philos_init(*p, *forks, (*p)->nb_philo);
	if (philos == NULL)
	{
		forks_destroy(forks, (*p)->nb_philo);
		pthread_mutex_destroy(&((*p)->end));
		free(*p);
		*p = NULL;
		return (NULL);
	}
	return (philos);
}
