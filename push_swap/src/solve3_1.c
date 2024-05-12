/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve3_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 10:44:42 by rchan--r          #+#    #+#             */
/*   Updated: 2022/12/12 11:19:10 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	solve3_case312(t_stack **head_a, char ***instr)
{
	return (stk_rotate(head_a, instr, RA));
}

int	solve3_case213(t_stack **head_a, char ***instr)
{
	return (stk_swap(head_a, instr, SA));
}

int	solve3_case321(t_stack **head_a, char ***instr)
{
	if (stk_swap(head_a, instr, SA) == 0)
		return (0);
	return (stk_rev_rotate(head_a, instr, RRA));
}

int	solve3_case231(t_stack **head_a, char ***instr)
{
	return (stk_rev_rotate(head_a, instr, RRA));
}

int	solve3_case132(t_stack **head_a, char ***instr)
{
	if (stk_rev_rotate(head_a, instr, RRA) == 0)
		return (0);
	return (stk_swap(head_a, instr, SA));
}
