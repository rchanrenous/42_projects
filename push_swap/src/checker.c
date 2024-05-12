/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:37:09 by rchan--r          #+#    #+#             */
/*   Updated: 2022/12/13 21:29:42 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	instr_code(char *line)
{
	if (line == NULL)
		return (-1);
	if (ft_strncmp(line, "rra", 3) == 0 && ft_strlen(line) == 4)
		return (RRA);
	if (ft_strncmp(line, "rrb", 3) == 0 && ft_strlen(line) == 4)
		return (RRB);
	if (ft_strncmp(line, "rrr", 3) == 0 && ft_strlen(line) == 4)
		return (RRR);
	if (ft_strncmp(line, "sa", 2) == 0 && ft_strlen(line) == 3)
		return (SA);
	if (ft_strncmp(line, "sb", 2) == 0 && ft_strlen(line) == 3)
		return (SB);
	if (ft_strncmp(line, "ss", 2) == 0 && ft_strlen(line) == 3)
		return (SS);
	if (ft_strncmp(line, "pa", 2) == 0 && ft_strlen(line) == 3)
		return (PA);
	if (ft_strncmp(line, "pb", 2) == 0 && ft_strlen(line) == 3)
		return (PB);
	if (ft_strncmp(line, "ra", 2) == 0 && ft_strlen(line) == 3)
		return (RA);
	if (ft_strncmp(line, "rb", 2) == 0 && ft_strlen(line) == 3)
		return (RB);
	if (ft_strncmp(line, "rr", 2) == 0 && ft_strlen(line) == 3)
		return (RR);
	return (-1);
}

int	stk_exec_instr(t_stack **head_a, t_stack **head_b, char ***instr, int code)
{
	if (code == SA)
		return (stk_swap(head_a, instr, SA));
	if (code == SB)
		return (stk_swap(head_b, instr, SB));
	if (code == SS)
		return (stk_swap_both(head_a, head_b, instr));
	if (code == PA)
		return (stk_push(head_b, head_a, instr, PA));
	if (code == PB)
		return (stk_push(head_a, head_b, instr, PB));
	if (code == RA)
		return (stk_rotate(head_a, instr, RA));
	if (code == RB)
		return (stk_rotate(head_b, instr, RB));
	if (code == RR)
		return (stk_rotate_both(head_a, head_b, instr));
	if (code == RRA)
		return (stk_rev_rotate(head_a, instr, RRA));
	if (code == RRB)
		return (stk_rev_rotate(head_b, instr, RRB));
	if (code == RRR)
		return (stk_rev_rotate_both(head_a, head_b, instr));
	return (0);
}

void	free_line(char **line)
{
	free(*line);
	*line = NULL;
}
