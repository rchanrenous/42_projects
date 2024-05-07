/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:10:35 by rchan--r          #+#    #+#             */
/*   Updated: 2023/01/11 13:31:02 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	char	**map;
	int		len_line;
	int		nb_line;
	//char	**map_dup;

	if (argc != 2)
		return (0);
	//map = read_input(argv[1]);
	map = map_read(argv[1], &len_line, &nb_line);
	if (map == NULL)
		return (0);
	ft_printf("my map\n");
	map_print(map);

	/* map_duplicate

	map_dup = map_duplicate(map);
	if (map_dup == NULL)
		return (map_free(&map), 0);
	map_print(map_dup);
	map_free(&map);
	map_free(&map_dup);
	*/

//	ft_printf("map_is_valid: %d\n", map_is_valid(map)); //static variable!
	map_free(&map);
}
