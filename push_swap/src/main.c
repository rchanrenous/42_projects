/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 12:49:55 by rchan--r          #+#    #+#             */
/*   Updated: 2022/12/11 20:52:22 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*head_a;
	t_stack	*head_b;
	char	**instr;

	init_push_swap(&head_a, &head_b, &instr);
	if (read_input(&head_a, argv + 1, argc - 1) == 0)
		ft_printf("Error\n");
	else if (solve(&head_a, &head_b, &instr, argc - 1) == 0)
		ft_printf("Error\n");
	else
		instr_print_opti(instr);
	stk_free(&head_a);
	stk_free(&head_b);
	instr_free(&instr);
}
