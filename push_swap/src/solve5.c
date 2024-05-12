/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:51:52 by rchan--r          #+#    #+#             */
/*   Updated: 2022/12/11 19:09:39 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	solve5_insert(t_stack **head_a, t_stack **head_b, char ***instr)
{
	if (node_insert(head_a, head_b, *head_b, instr) == 0)
		return (0);
	if (stk_length(*head_b) == 0)
		return (1);
	return (node_insert(head_a, head_b, *head_b, instr));
}
