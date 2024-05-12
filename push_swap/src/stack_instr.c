/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 05:49:55 by rchan--r          #+#    #+#             */
/*   Updated: 2022/12/12 11:20:27 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	stk_push(t_stack **src, t_stack **dst, char ***instr, int s)
{
	t_stack	*tmp;
	char	*str;

	if (s != PA && s != PB)
		return (0);
	if (src == NULL || dst == NULL || *src == NULL)
		return (0);
	if (*src == NULL)
		return (0);
	tmp = (*src)->next;
	(*src)->next = *dst;
	*dst = *src;
	*src = tmp;
	str = instr_str(s);
	if (str == NULL)
		return (0);
	return (instr_write(instr, str));
}

int	stk_swap(t_stack **stk, char ***instr, int s)
{
	t_stack	*tmp;
	char	*str;

	if (s != SA && s != SB && s != -1)
		return (0);
	if (stk == NULL || *stk == NULL || (*stk)->next == NULL)
		return (0);
	tmp = *stk;
	*stk = (*stk)->next;
	tmp->next = (*stk)->next;
	(*stk)->next = tmp;
	if (s != -1)
	{
		str = instr_str(s);
		if (str == NULL)
			return (0);
		return (instr_write(instr, str));
	}
	return (1);
}

int	stk_swap_both(t_stack **head_a, t_stack **head_b, char ***instr)
{
	char	*str;

	if (stk_swap(head_a, instr, -1) == 0 || stk_swap(head_b, instr, -1) == 0)
		return (0);
	str = instr_str(SS);
	if (str == NULL)
		return (0);
	return (instr_write(instr, str));
}

int	stk_rotate(t_stack **head, char ***instr, int s)
{
	char	*str;
	t_stack	*tail;

	tail = stk_tail(*head);
	if (head == NULL || tail == NULL || (s != RA && s != RB && s != -1))
		return (0);
	if (*head == NULL || tail == *head)
		return (0);
	tail->next = *head;
	*head = (*head)->next;
	tail = tail->next;
	tail->next = NULL;
	if (s != -1)
	{
		str = instr_str(s);
		if (str == NULL)
			return (0);
		return (instr_write(instr, str));
	}
	return (1);
}

int	stk_rev_rotate(t_stack **head, char ***instr, int s)
{
	char	*str;
	t_stack	*tmp;
	t_stack	*tail;

	tail = stk_tail(*head);
	if (head == NULL || tail == NULL || (s != RRA && s != RRB && s != -1))
		return (0);
	if (*head == NULL || tail == *head)
		return (0);
	tmp = stk_before_tail(*head);
	tail->next = *head;
	*head = tail;
	tmp->next = NULL;
	tail = tmp;
	if (s != -1)
	{
		str = instr_str(s);
		if (str == NULL)
			return (0);
		return (instr_write(instr, str));
	}
	return (1);
}
