/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_instr2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 05:49:55 by rchan--r          #+#    #+#             */
/*   Updated: 2022/12/12 11:21:30 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	stk_rotate_both(t_stack **head_a, t_stack **head_b, char ***instr)
{
	char	*str;

	if (stk_rotate(head_a, instr, -1) == 0)
		return (0);
	if (stk_rotate(head_b, instr, -1) == 0)
		return (0);
	str = instr_str(RR);
	if (str == NULL)
		return (0);
	return (instr_write(instr, str));
}

int	stk_rev_rotate_both(t_stack **head_a, t_stack **head_b, char ***instr)
{
	char	*str;

	if (stk_rev_rotate(head_a, instr, -1) == 0)
		return (0);
	if (stk_rev_rotate(head_b, instr, -1) == 0)
		return (0);
	str = instr_str(RRR);
	if (str == NULL)
		return (0);
	return (instr_write(instr, str));
}

int	stk_exec_r_instr(t_stack **head, int nb, char ***instr, char c)
{
	int		i;
	int		s;

	if (nb < 0)
		return (0);
	i = 0;
	if (c == 'A')
		s = RA;
	else if (c == 'B')
		s = RB;
	else
		return (0);
	while (i < nb)
	{
		if (stk_rotate(head, instr, s) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	stk_exec_r_r_instr(t_stack **head, int nb, char ***instr, char c)
{
	int		i;
	int		s;

	if (nb < 0)
		return (0);
	i = 0;
	if (c == 'A')
		s = RRA;
	else if (c == 'B')
		s = RRB;
	else
		return (0);
	while (i < nb)
	{
		if (stk_rev_rotate(head, instr, s) == 0)
			return (0);
		i++;
	}
	return (1);
}
