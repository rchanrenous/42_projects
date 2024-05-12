/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 22:19:31 by rchan--r          #+#    #+#             */
/*   Updated: 2022/09/21 23:02:05 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	instr_code(char *res, int t, int u, int last)
{
	res[last] = '\0';
	if (u == 0)
		res[last - 1] = 'a';
	if (u == 1)
		res[last - 1] = 'b';
	if (u == 2)
	{
		if (t == 2 || t == 3)
			res[last - 1] = 'r';
		if (t == 0)
			res[last - 1] = 's';
	}
	if (t == 0)
		res[last - 2] = 's';
	if (t == 1)
		res[last - 2] = 'p';
	if (t == 2 || t == 3)
		res[last - 2] = 'r';
	if (t == 3)
		res[0] = 'r';
}

char	*instr_str(int s)
{
	char	*res;
	int		last;

	if (s == RRA || s == RRB || s == RRR)
	{
		res = malloc(sizeof(char) * 4);
		last = 3;
	}
	else
	{
		res = malloc(sizeof(char) * 3);
		last = 2;
	}
	if (res == NULL)
		return (NULL);
	instr_code(res, s / 10, s % 10, last);
	return (res);
}

void	instr_free(char ***instr)
{
	int	i;

	if (instr == NULL || *instr == NULL)
		return ;
	i = 0;
	while ((*instr)[i] != NULL)
	{
		free((*instr)[i]);
		i++;
	}
	free(*instr);
	*instr = NULL;
}
