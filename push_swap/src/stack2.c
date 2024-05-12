/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 13:56:15 by rchan--r          #+#    #+#             */
/*   Updated: 2022/12/09 12:01:05 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*stk_tail(t_stack *head)
{
	t_stack	*tail;

	if (head == NULL)
		return (NULL);
	tail = head;
	while (tail->next != NULL)
		tail = tail->next;
	return (tail);
}

t_stack	*stk_before_tail(t_stack *head)
{
	t_stack	*res;

	if (head == NULL || head->next == NULL)
		return (NULL);
	res = head;
	while (res->next->next != NULL)
		res = res->next;
	return (res);
}

int	stk_length(t_stack *head)
{
	int	n;

	if (head == NULL)
		return (0);
	n = 1;
	while (head->next != NULL)
	{
		head = head->next;
		n++;
	}
	return (n);
}

t_stack	*stk_smallest(t_stack *head)
{
	t_stack	*res;

	if (head == NULL)
		return (NULL);
	res = head;
	while (head->next != NULL)
	{
		head = head->next;
		if (res->i > head->i)
			res = head;
	}
	return (res);
}

int	stk_order(t_stack **head, char ***instr, char c)
{
	t_stack	*smallest;

	if (head == NULL || *head == NULL)
		return (0);
	smallest = stk_smallest(*head);
	if (node_to_top(head, smallest, instr, c) == 0)
		return (0);
	if (stk_is_sorted(*head) == 1)
		return (1);
	return (-1);
}
