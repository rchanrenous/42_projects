/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:08:45 by rchan--r          #+#    #+#             */
/*   Updated: 2022/12/13 14:35:09 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
void	init_push_swap(t_stack **ha, t_stack **ta, t_stack **hb, t_stack **tb)
{
	*ha = NULL;
	*hb = NULL;
	*ta = NULL;
	*tb = NULL;
}*/

void	init_push_swap(t_stack **head_a, t_stack **head_b, char ***instr)
{
	*head_a = NULL;
	*head_b = NULL;
	*instr = NULL;
}

static long	ft_atol_int(char *str)
{
	long	res;
	int		i;
	int		minus;

	res = 0;
	i = 0;
	minus = 0;
	if (str == NULL || str[0] == '\0')
		return ((long)INT_MAX + 1);
	if (str[i] == '-')
	{
		minus = 1;
		i++;
	}
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return ((long)INT_MAX + 1);
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (minus == 1)
		return (-res);
	return (res);
}

static int	is_int(long l)
{
	if (l >= INT_MIN && l <= INT_MAX)
		return (1);
	return (0);
}

int	read_input(t_stack **head, char **argv, int argc)
{
	int		i;
	long	l;
	t_stack	*new;
	t_stack	*tail;

	i = 0;
	if (head == NULL)
		return (0);
	tail = *head;
	while (i < argc)
	{
		l = ft_atol_int(argv[i]);
		if (!is_int(l) || !stk_no_duplicate(*head, (int)l))
			return (stk_free(head), 0);
		new = stknew((int)l);
		if (new == NULL)
			return (stk_free(head), 0);
		if (*head == NULL)
			*head = new;
		stkadd_back(&tail, new);
		tail = new;
		i++;
	}
	return (1);
}
