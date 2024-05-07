/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 07:42:10 by sadorlin          #+#    #+#             */
/*   Updated: 2023/07/19 15:27:25 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	file_exist(char *file)
{
	int		size;
	int		fd;
	int		buff[3];

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror(file), 1);
	size = read(fd, buff, 2);
	close(fd);
	if (size < 0)
	{
		write(2, "Error.\nCannot read : '", 22);
		write(2, file, ft_strlen(file));
		write(2, "'\n", 2);
	}
	else if (size == 0)
	{
		write(2, "Error.\n'", 8);
		write(2, file, ft_strlen(file));
		write(2, "' : is empty.\n", 14);
	}
	else
		return (0);
	return (1);
}

static int	filename_is_valid(char *file)
{
	int	size;

	size = ft_strlen(file);
	if (file[size - 1] == 'b' && file[size - 2] == 'u'
		&& file[size - 3] == 'c' && file[size - 4] == '.'
		&& file[size - 5] && file[size - 5] != '/')
		return (0);
	write(2, "Error.\n'", 8);
	write(2, file, size);
	write(2, "\' : invalid filename.\n", 22);
	write(2, "Usage : <./cub3d> <filename.cub>\n", 33);
	return (1);
}

int	check_argv(int ac, char **av)
{
	if (ac == 1)
		return (write(2, "Error.\nArgument missing.\n", 25));
	if (ac > 2)
		return (write(2, "Error.\nToo many arguments.\n", 27));
	if (filename_is_valid(av[1]))
		return (1);
	if (file_exist(av[1]))
		return (1);
	return (0);
}
