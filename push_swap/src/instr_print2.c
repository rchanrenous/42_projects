/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_print2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 09:54:51 by rchan--r          #+#    #+#             */
/*   Updated: 2022/12/12 09:55:13 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	instr_print_n_both(char c, int last, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		write(1, &c, 1);
		if (last == 2)
			write(1, &c, 1);
		write(1, "\n", 1);
		i++;
	}
}

static void	instr_print_n_times(char c, int last, char l, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		if (last == 2)
			write(1, &c, 1);
		write(1, &l, 1);
		write(1, "\n", 1);
		i++;
	}
}

void	instr_print_ab(char	*str, int count_a, int count_b)
{
	int	last;

	last = 1;
	if (str[1] == 'r')
		last = 2;
	if (count_a > count_b)
	{
		instr_print_n_both(str[0], last, count_b);
		instr_print_n_times(str[0], last, 'a', count_a - count_b);
	}
	else
	{
		instr_print_n_both(str[0], last, count_a);
		instr_print_n_times(str[0], last, 'b', count_b - count_a);
	}
}
