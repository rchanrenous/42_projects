/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:47:50 by rchan--r          #+#    #+#             */
/*   Updated: 2022/12/12 09:30:31 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	stk_rank(t_stack *head, int i)
{
	int		res;
	t_stack	*tmp;

	if (head == NULL)
		return (-1);
	tmp = head;
	res = 1;
	while (tmp != NULL)
	{
		if (tmp->i < i)
			res++;
		tmp = tmp->next;
	}
	return (res);
}

long	stk_median(t_stack *head)
{
	t_stack	*candidate;
	int		len;
	int		rank;

	if (head == NULL)
		return ((long)INT_MAX + 1);
	candidate = head;
	len = stk_length(head);
	while (candidate != NULL)
	{
		rank = stk_rank(head, candidate->i);
		if (rank == len / 2)
			return ((long)(candidate->i));
		candidate = candidate->next;
	}
	return ((long)INT_MIN - 1);
}

int	stk_push_median(t_stack **head_a, t_stack **head_b, int mdn, char ***instr)
{
	t_stack	*tmp;

	if (head_a == NULL || *head_a == NULL)
		return (0);
	tmp = *head_a;
	while (tmp != NULL)
	{
		if (tmp->i <= mdn)
		{
			if (node_to_top(head_a, tmp, instr, 'A') == 0)
				return (0);
			return (stk_push(head_a, head_b, instr, PB));
		}
		tmp = tmp->next;
	}
	return (-1);
}
