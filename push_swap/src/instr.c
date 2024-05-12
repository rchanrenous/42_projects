/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 18:49:08 by rchan--r          #+#    #+#             */
/*   Updated: 2022/12/12 09:20:32 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* does not free in case of error! (helps freeing when extend is called))*/
static int	instr_fill(char ***instr, int size)
{
	int	i;

	if (size < 1)
		return (0);
	i = 0;
	while (i < size)
	{
		(*instr)[i] = malloc(sizeof(char));
		if ((*instr)[i] == NULL)
			return (0);
		(*instr)[i][0] = '\0';
		i++;
	}
	(*instr)[size] = NULL;
	return (1);
}

static int	instr_init(char ***instr)
{
	if (instr == NULL)
		return (0);
	*instr = malloc(sizeof(char *) * (INIT_SIZE + 1));
	if (*instr == NULL)
		return (0);
	if (instr_fill(instr, INIT_SIZE) == 0)
	{
		instr_free(instr);
		return (0);
	}
	return (1);
}

static void	instr_copy(char **src, char **dst, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
}

static int	instr_extend(char ***instr)
{
	static int	k = 2;
	char		**new;
	char		**tmp;

	new = malloc(sizeof(char *) * (k * INIT_SIZE + 1));
	if (new == NULL)
	{
		instr_free(instr);
		return (0);
	}
	instr_copy(*instr, new, (k - 1) * INIT_SIZE);
	tmp = new + (k - 1) * INIT_SIZE;
	if (instr_fill(&tmp, INIT_SIZE) == 0)
	{
		instr_free(&new);
		instr_free(instr);
		instr = NULL;
		return (0);
	}
	k++;
	free(*instr);
	*instr = new;
	return (1);
}

int	instr_write(char ***instr, char *str)
{
	static int	next_empty = 0;

	if (instr == NULL)
		return (0);
	if (*instr == NULL)
	{
		if (instr_init(instr) == 0)
			return (0);
	}
	if ((*instr)[next_empty] == NULL)
	{
		if (instr_extend(instr) == 0)
			return (0);
	}
	free((*instr)[next_empty]);
	(*instr)[next_empty] = str;
	next_empty++;
	return (1);
}
