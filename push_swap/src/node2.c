/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:53:49 by rchan--r          #+#    #+#             */
/*   Updated: 2022/12/12 09:24:12 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	node_nb_operation(t_stack *head_a, t_stack *head_b, t_stack *node_b)
{
	int	nb_to_top;
	int	nb_next_to_top;
	int	direction;

	if (head_b == NULL || node_b == NULL)
		return (-1);
	node_find_next(head_a, &nb_next_to_top, node_b->i);
	nb_to_top = node_nb_top(head_b, node_b, &direction);
	if (nb_to_top == -1)
		return (-1);
	return (nb_to_top + nb_next_to_top);
}

t_stack	*node_next_to_insert(t_stack *head_a, t_stack *head_b)
{
	t_stack	*res;
	t_stack	*tmp;
	int		nb;
	int		save;

	if (head_b == NULL)
		return (NULL);
	tmp = head_b;
	res = head_b;
	save = node_nb_operation(head_a, head_b, tmp);
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		nb = node_nb_operation(head_a, head_b, tmp);
		if (nb < save)
		{
			save = nb;
			res = tmp;
		}
	}
	return (res);
}
