/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 22:33:19 by rchan--r          #+#    #+#             */
/*   Updated: 2022/12/11 21:43:26 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*stknew(int i)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (new == NULL)
		return (NULL);
	new->i = i;
	new->next = NULL;
	return (new);
}

void	stkadd_back(t_stack **stk, t_stack *new)
{
	t_stack	*tmp;

	if (stk == NULL)
		return ;
	if (*stk == NULL)
		*stk = new;
	else
	{
		tmp = *stk;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	stk_no_duplicate(t_stack *stk, int i)
{
	while (stk != NULL)
	{
		if (stk->i == i)
			return (0);
		stk = stk->next;
	}
	return (1);
}

void	stk_free(t_stack **stk)
{
	if (stk == NULL || *stk == NULL)
		return ;
	if ((*stk)->next == NULL)
		free(*stk);
	else
	{
		stk_free(&((*stk)->next));
		free((*stk));
	}
	*stk = NULL;
}

int	stk_is_sorted(t_stack *stk)
{
	int	tmp;

	if (stk == NULL)
		return (1);
	tmp = stk->i;
	while (stk->next != NULL)
	{
		stk = stk->next;
		if (tmp > stk->i)
			return (0);
		else
			tmp = stk->i;
	}
	return (1);
}
