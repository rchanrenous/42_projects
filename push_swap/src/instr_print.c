/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 21:50:52 by rchan--r          #+#    #+#             */
/*   Updated: 2022/12/05 10:57:58 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	instr_which_stack(char *str, int *count_a, int *count_b)
{
	int	last;

	last = 1;
	if (str[1] == 'r')
		last = 2;
	if (str[last] == 'a')
		(*count_a)++;
	else
		(*count_b)++;
}

static int	instr_end_prefix(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 2)
		return (0);
	if (len == 3)
		return (1);
	return (-1);
}

static int	instr_is_both(char *str)
{
	int		len;
	char	c;

	len = ft_strlen(str);
	if (len == 2)
		c = str[1];
	else
		c = str[2];
	if (c == 'a' || c == 'b')
		return (0);
	return (1);
}

static int	instr_same_prefix(char *str1, char *str2)
{
	int	end_prefix;

	end_prefix = instr_end_prefix(str1);
	if (ft_strncmp(str1, "", 1) == 0 || ft_strncmp(str2, "", 1) == 0)
		return (0);
	if (instr_is_both(str1) || instr_is_both(str2))
		return (0);
	if (ft_strncmp(str1, str2, end_prefix + 1) != 0)
		return (0);
	end_prefix = instr_end_prefix(str2);
	if (ft_strncmp(str1, str2, end_prefix + 1) != 0)
		return (0);
	return (1);
}

void	instr_print_opti(char **instr)
{
	int		i;
	int		count_a;
	int		count_b;

	if (instr == NULL || instr[0] == NULL)
		return ;
	if (ft_strncmp(instr[0], "", 1) == 0)
		return ;
	if (instr[0][0] == 'p' || instr_is_both(instr[0]) == 1)
	{
		ft_printf("%s\n", instr[0]);
		instr_print_opti(instr + 1);
		return ;
	}
	count_a = 0;
	count_b = 0;
	instr_which_stack(instr[0], &count_a, &count_b);
	i = 1;
	while (instr[i] != NULL && instr_same_prefix(instr[i], instr[0]) == 1)
	{
		instr_which_stack(instr[i], &count_a, &count_b);
		i++;
	}
	instr_print_ab(instr[0], count_a, count_b);
	instr_print_opti(instr + i);
}
