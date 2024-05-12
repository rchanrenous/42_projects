/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 23:17:33 by rchan--r          #+#    #+#             */
/*   Updated: 2022/12/12 09:56:18 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
void	instr_print_debug(char **instr)
{
	int	i;

	if (instr == NULL)
	{
		ft_printf("\n");
		return ;
	}
	if (instr[0] != NULL)
	{
		ft_printf("0: %s", instr[0]);
		i = 1;
		while (instr[i] != NULL)
		{
			ft_printf("  %d: %s", i, instr[i]);
			i++;
		}
		ft_printf("\n");
	}
}*/

/*
void	instr_print(char **instr)
{
	int		i;
	char	*tmp;

	if (instr == NULL)
		return ;
	i = 0;
	tmp = instr[i];
	while (tmp != NULL && ft_strncmp(tmp, "", ft_strlen(tmp) + 1) != 0)
	{
		ft_printf("%s\n", tmp);
		i++;
		tmp = instr[i];
	}
}*/

/*
void	instr_print_full(char **instr)
{
	if (instr == NULL)
		return ;
	ft_printf("no opti:\n");
	instr_print_debug(instr);
	instr_print(instr);
	ft_printf("opti:\n");
	instr_print_opti(instr);
}*/
