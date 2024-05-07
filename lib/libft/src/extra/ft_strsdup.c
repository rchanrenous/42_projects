/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadorlin <sadorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:26:31 by sadorlin          #+#    #+#             */
/*   Updated: 2023/07/12 00:16:56 by sadorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsdup(char **strs)
{
	int		i;
	int		j;
	char	**dest;

	i = -1;
	j = 0;
	if (!strs)
		return (NULL);
	while (strs[j])
		j++;
	dest = malloc(sizeof(char *) * (j + 1));
	if (!dest)
		return (NULL);
	while (++i < j)
	{
		dest[i] = ft_strdup(strs[i]);
		if (!dest[i])
		{
			free_strs(dest);
			return (NULL);
		}
	}
	dest[i] = NULL;
	return (dest);
}
