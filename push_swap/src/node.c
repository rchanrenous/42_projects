/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:59:54 by rchan--r          #+#    #+#             */
/*   Updated: 2022/12/12 12:18:36 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	node_nb_top(t_stack *head, t_stack *node, int *direction)
{
	int	top;
	int	bottom;

	if (head != NULL && node == NULL)
		return (-1);
	top = 0;
	while (head != NULL && head != node)
	{
		head = head->next;
		top++;
	}
	if (head == NULL && node != NULL)
		return (-1);
	bottom = stk_length(node);
	if (top < bottom)
	{
		*direction = 1;
		return (top);
	}
	*direction = -1;
	return (bottom);
}

int	node_to_top(t_stack **head, t_stack *node, char ***instr, char c)
{
	int		direction;
	int		nb;

	nb = node_nb_top(*head, node, &direction);
	if (nb == -1)
		return (0);
	if (direction == 1)
		return (stk_exec_r_instr(head, nb, instr, c));
	else
		return (stk_exec_r_r_instr(head, nb, instr, c));
}

static int	node_find_update(int ri, int hi, int i)
{
	if ((ri < i && !(ri <= hi && hi < i)) || (ri >= i && hi >= i && hi < ri))
		return (1);
	return (0);
}

t_stack	*node_find_next(t_stack *head, int *nb, int i)
{
	t_stack	*res;
	int		j;
	int		bottom;

	*nb = 0;
	if (head == NULL)
		return (NULL);
	res = head;
	j = 0;
	while (head->next != NULL)
	{
		head = head->next;
		j++;
		if (node_find_update(res->i, head->i, i) == 1)
		{
			res = head;
			*nb = j;
		}
	}
	bottom = stk_length(res);
	if (bottom < *nb)
		*nb = bottom;
	return (res);
}

int	node_insert(t_stack **hd_a, t_stack **hd_b, t_stack *node_b, char ***instr)
{
	t_stack	*next_a;
	int		nb;

	if (hd_a == NULL || hd_b == NULL || *hd_b == NULL || node_b == NULL)
		return (0);
	next_a = node_find_next(*hd_a, &nb, node_b->i);
	if (node_to_top(hd_a, next_a, instr, 'A') == 0)
		return (0);
	if (node_to_top(hd_b, node_b, instr, 'B') == 0)
		return (0);
	return (stk_push(hd_b, hd_a, instr, PA));
}
