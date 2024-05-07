/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_color_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 11:18:32 by sadorlin          #+#    #+#             */
/*   Updated: 2023/07/21 15:13:19 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	char_to_int(char *color, int i, int val)
{
	while (color[i] && color[i] == ' ')
		i++;
	while (color[i])
	{
		if (color[i] == ' ')
		{
			while (color[i] && color[i] == ' ')
				i++;
			if (color[i])
				return (write(2, "Error.\nInvalid color.\n", 22), -1);
			break ;
		}
		val = (val * 10) + (color[i] - 48);
		if (val > 255)
			return (write(2, "Error.\nInvalid color.\n", 22), -1);
		i++;
	}
	return (val);
}

static int	convert_rgb(t_parse *prs, char c)
{
	int	r;
	int	g;
	int	b;

	r = char_to_int(prs->tmp[0], 0, 0);
	g = char_to_int(prs->tmp[1], 0, 0);
	b = char_to_int(prs->tmp[2], 0, 0);
	if (r == -1 || b == -1 || g == -1)
		return (1);
	if (c == 'C')
		prs->ceiling = (r << 16 | g << 8 | b);
	else
		prs->floor = (r << 16 | g << 8 | b);
	return (0);
}

static int	check_color_element(char *tp, int i, int comma, int ret)
{
	while (tp[++i])
	{
		if (tp[i] != ' ' && tp[i] != ','
			&& !(tp[i] >= '0' && tp[i] <= '9'))
			ret = 1;
		else if (tp[i] == ',')
			comma++;
		if (ret || comma > 2)
			return (write(2, "Error.\nInvalid color.\n", 22), 1);
	}
	if (comma != 2)
		return (write(2, "Error.\nInvalid color.\n", 22), 1);
	return (0);
}

int	fill_color_param(t_parse *prs, char *tp)
{
	if (check_color_element(tp, 0, 0, 0))
		return (1);
	prs->tmp = ft_split(&tp[1], ',');
	if (!prs->tmp)
		return (perror("Malloc() fill_color() "), 1);
	if (size_strs(prs->tmp) != 3)
		return (write(2, "Error.\nInvalid color.\n", 22), 1);
	if (convert_rgb(prs, tp[0]))
		return (1);
	free_strs(prs->tmp);
	prs->tmp = NULL;
	return (0);
}
