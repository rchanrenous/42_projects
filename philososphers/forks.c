/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 22:32:53 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/30 22:44:20 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks_destroy(t_mutex ***forks, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy((*forks)[i]);
		free((*forks)[i]);
		i++;
	}
	free(*forks);
	*forks = NULL;
}

t_mutex	**forks_init(int nb_philo)
{
	t_mutex	**forks;
	int		i;

	forks = malloc(sizeof(t_mutex *) * (nb_philo));
	if (forks == NULL)
		return (NULL);
	i = 0;
	while (i < nb_philo)
	{
		forks[i] = malloc(sizeof(t_mutex));
		if (forks[i] == NULL)
			return (forks_destroy(&forks, i), NULL);
		if (pthread_mutex_init(forks[i], NULL) != 0)
			return (free(forks[i]), forks_destroy(&forks, i), NULL);
		i++;
	}
	return (forks);
}
