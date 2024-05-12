/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 10:44:42 by rchan--r          #+#    #+#             */
/*   Updated: 2022/12/12 11:18:33 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	solve3(t_stack **head_a, char ***instr)
{
	int	top;
	int	middle;
	int	bottom;

	get_values3(*head_a, &top, &middle, &bottom);
	if (top > middle && bottom > middle && bottom < top)
		return (solve3_case312(head_a, instr));
	else if (top > middle && bottom > middle && bottom > top)
		return (solve3_case213(head_a, instr));
	else if (top > middle && middle > bottom)
		return (solve3_case321(head_a, instr));
	else if (top < middle && bottom < middle && top > bottom)
		return (solve3_case231(head_a, instr));
	else if (top < middle && bottom < middle && bottom > top)
		return (solve3_case132(head_a, instr));
	return (1);
}

static int	solve5(t_stack **head_a, t_stack **head_b, char ***instr)
{
	if (stk_push(head_a, head_b, instr, PB) == 0)
		return (0);
	if (stk_length(*head_a) == 4 && stk_push(head_a, head_b, instr, PB) == 0)
		return (0);
	if (solve3(head_a, instr) == 0)
		return (0);
	if (solve5_insert(head_a, head_b, instr) == 0)
		return (0);
	return (stk_order(head_a, instr, 'A'));
}

static int	solve100(t_stack **head_a, t_stack **head_b, char ***instr)
{
	t_stack	*next;

	if (head_a == NULL || *head_a == NULL)
		return (0);
	while (*head_a != NULL)
	{
		if (stk_push(head_a, head_b, instr, PB) == 0)
			return (0);
	}
	while (*head_b != NULL)
	{
		next = node_next_to_insert(*head_a, *head_b);
		if (node_insert(head_a, head_b, next, instr) == 0)
			return (0);
	}
	if (stk_order(head_a, instr, 'A') == 1)
		return (1);
	return (0);
}

static int	solve500(t_stack **head_a, t_stack **head_b, char ***instr)
{
	long	median;
	int		tmp;

	if (head_a == NULL || *head_a == NULL)
		return (0);
	while (*head_a != NULL && (*head_a)->next != NULL)
	{
		median = stk_median(*head_a);
		if (median >= INT_MAX || median <= INT_MIN)
			return (0);
		tmp = stk_push_median(head_a, head_b, median, instr);
		while (tmp != -1)
		{
			if (tmp == 0)
				return (0);
			tmp = stk_push_median(head_a, head_b, median, instr);
		}
	}
	return (solve100(head_a, head_b, instr));
}

int	solve(t_stack **head_a, t_stack **head_b, char ***instr, int argc)
{
	if (stk_is_sorted(*head_a) == 1)
		return (1);
	else if (argc == 2)
		return (stk_rotate(head_a, instr, RA));
	else if (argc <= 3)
		return (solve3(head_a, instr));
	else if (argc <= 5)
		return (solve5(head_a, head_b, instr));
	else if (argc <= 100)
		return (solve100(head_a, head_b, instr));
	else
		return (solve500(head_a, head_b, instr));
}
