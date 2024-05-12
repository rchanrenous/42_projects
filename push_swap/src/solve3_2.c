/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve3_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 10:44:42 by rchan--r          #+#    #+#             */
/*   Updated: 2022/10/01 11:23:05 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	get_values3(t_stack *head_a, int *top, int *middle, int *bottom)
{
	*top = head_a->i;
	*middle = head_a->next->i;
	*bottom = head_a->next->next->i;
}
