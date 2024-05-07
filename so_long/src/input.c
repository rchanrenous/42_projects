/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:46:46 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/16 16:56:45 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	filename_valid(char *filename)
{
	int	len;

	if (filename == NULL)
		return (ft_printf("Error\n"), 0);
	if (*filename == '.')
		return (ft_printf("Error\nInvalid file name.\n"), 0);
	len = ft_strlen(filename);
	filename = ft_strnstr(filename, ".ber", len);
	if (filename == NULL || *(filename + 4) != '\0')
		return (ft_printf("Error\nInvalid file name.\n"), 0);
	return (1);
}

static void	line_trim_nl(char *line)
{
	int	len;

	if (line == NULL)
		return ;
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static void	map_fit(char **map)
{
	if (map == NULL)
		return ;
	while (*map != NULL)
	{
		if (ft_strncmp(*map, "\0", 1) == 0)
		{
			free(*map);
			*map = NULL;
		}
		map++;
	}
}

char	**map_read(char *filename, int *len_line, int *nb_line)
{
	char	**map;
	char	*line;
	int		fd;

	map = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\nInvalid input file.\n"), NULL);
	line = get_next_line(fd);
	line_trim_nl(line);
	while (line != NULL)
	{
		if (ft_strncmp(line, "\0", 1) == 0)
			return (map_free(&map), NULL);
		if (map_append_line(&map, line) == 0)
			return (ft_printf("Error\n"), NULL);
		line = get_next_line(fd);
		line_trim_nl(line);
	}
	close(fd);
	map_fit(map);
	if (map_is_valid(map, len_line, nb_line) == 0)
		return (map_free(&map), NULL);
	return (map);
}

int	init_so_long(t_mlx **mlx, char *filename)
{
	int		len_line;
	int		nb_line;
	char	**map;

	if (mlx == NULL)
		return (ft_printf("Error\n"), 0);
	map = map_read(filename, &len_line, &nb_line);
	if (map == NULL)
		return (0);
	*mlx = t_mlx_init(map, len_line, nb_line);
	if (*mlx == NULL)
		return (0);
	map_find(map, 'E', &((*mlx)->e_i), &((*mlx)->e_j));
	return (1);
}
