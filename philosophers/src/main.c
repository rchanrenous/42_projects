/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:44:31 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/30 23:35:17 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	**philos;
	t_param	*param;
	t_mutex	**forks;

	(void) philos;
	param = read_input(argc - 1, argv + 1);
	if (param == NULL)
		return (0);
	if (param->nb_philo == 1)
	{
		printf("\033[1;33m%6d %d has taken a fork\n", 0, 1);
		printf("\033[1;31m%6ld %d died\033[0m\n", param->t2die + 1, 1);
		return (free(param), 0);
	}
	philos = init(&forks, &param);
	if (philos == NULL)
		return (0);
	if (threads_run(philos, param) == 0)
		printf("Error.\n");
	philos_destroy(&philos, param->nb_philo);
	forks_destroy(&forks, param->nb_philo);
	pthread_mutex_destroy(&(param->end));
	free(param);
}
