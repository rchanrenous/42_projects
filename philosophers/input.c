/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:16:41 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/31 02:00:51 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_atoli_ptr(long int *ptr, char *str)
{
	int	i;

	*ptr = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
		{
			*ptr = -1;
			return (-1);
		}
		(*ptr) = (*ptr) * 10 + str[i] - '0';
		i++;
	}
	return (*ptr);
}

int	ft_atoi_ptr(int *ptr, char *str)
{
	int	i;

	*ptr = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
		{
			*ptr = -1;
			return (-1);
		}
		(*ptr) = (*ptr) * 10 + str[i] - '0';
		i++;
	}
	return (*ptr);
}

t_param	*read_input(int argc, char **argv)
{
	t_param	*param;

	if (argc != 4 && argc != 5)
		return (NULL);
	param = malloc(sizeof(t_param));
	if (param == NULL)
		return (NULL);
	if (ft_atoi_ptr(&(param->nb_philo), argv[0]) <= 0)
		return (free(param), NULL);
	if (ft_atoli_ptr(&(param->t2die), argv[1]) <= 0)
		return (free(param), NULL);
	if (ft_atoli_ptr(&(param->t2eat), argv[2]) < 0)
		return (free(param), NULL);
	if (ft_atoli_ptr(&(param->t2sleep), argv[3]) < 0)
		return (free(param), NULL);
	if (argc == 5 && ft_atoi_ptr(&(param->nb_eat), argv[4]) <= 0)
		return (free(param), NULL);
	else if (argc == 4)
		param->nb_eat = -1;
	if (pthread_mutex_init(&(param->end), NULL) != 0)
		return (free(param), NULL);
	param->finished = 0;
	return (param);
}
