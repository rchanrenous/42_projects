/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_texture_param.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 12:08:22 by sadorlin          #+#    #+#             */
/*   Updated: 2023/07/19 16:37:45 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_texture_file(t_parse *prs, char *file)
{
	char	buff[3];
	int		size;

	prs->fd = open(file, O_RDONLY);
	if (prs->fd == -1)
		return (perror(file), 1);
	size = read(prs->fd, buff, 2);
	close(prs->fd);
	if (size < 0)
		return (write(2, "Error.\nTexture file unreadable.\n", 32));
	if (size == 0)
		return (write(2, "Error.\nTexture file empty.\n", 27));
	return (0);
}

static int	check_texture_filename(char *file)
{
	int	size;

	size = ft_strlen(file);
	if (file[size - 1] == 'm' && file[size - 2] == 'p'
		&& file[size - 3] == 'x' && file[size - 4] == '.'
		&& file[size - 5] && file[size - 5] != '/')
		return (0);
	write(2, "Error.\n'", 8);
	write(2, file, size);
	write(2, "\' : invalid texture filename.\n", 30);
	return (1);
}

static int	fill_texture(t_parse *prs, char *tex, char *tp)
{
	if (!ft_strncmp(tex, "NO ", 3))
		prs->no = ft_strdup(tp);
	else if (!ft_strncmp(tex, "SO ", 3))
		prs->so = ft_strdup(tp);
	else if (!ft_strncmp(tex, "WE ", 3))
		prs->we = ft_strdup(tp);
	else if (!ft_strncmp(tex, "EA ", 3))
		prs->ea = ft_strdup(tp);
	else
	{
		write(2, "Error.\nInvalid parameter : '", 28);
		write(2, tex, ft_strlen(tex));
		write(2, "'\n", 2);
		return (1);
	}
	return (0);
}

int	fill_texture_param(t_parse *prs, char *tex, char *tp)
{
	tp = ft_strtrim(&tex[3], " ");
	if (!tp)
		return (perror("Malloc() fill_texture() "), 1);
	if (fill_texture(prs, tex, tp))
		return (free(tp), 1);
	if (check_texture_filename(tp))
		return (free(tp), 1);
	if (check_texture_file(prs, tp))
		return (free(tp), 1);
	free(tp);
	return (0);
}
