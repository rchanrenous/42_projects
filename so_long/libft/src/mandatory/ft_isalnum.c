/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 18:07:40 by rchan--r          #+#    #+#             */
/*   Updated: 2022/01/17 18:40:12 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	int	a;
	int	d;

	a = ((c >= 97 && c <= 122) || (c >= 65 && c <= 90));
	d = (c >= 48 && c <= 57);
	return (a || d);
}
