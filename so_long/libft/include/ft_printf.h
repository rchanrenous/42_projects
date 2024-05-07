/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchan--r <rchan--r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:18:23 by rchan--r          #+#    #+#             */
/*   Updated: 2022/05/17 21:01:27 by rchan--r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

# if defined __APPLE__
#  define PTR_NULL "0x0"
# else 
#  define PTR_NULL "(nil)"
# endif

# define STR_NULL "(null)"

int		ft_printf(const char *str, ...);
void	ft_print_ptr(size_t l);
void	ft_print_ptr_hexa(size_t l);
void	ft_print_ptr_upper_hexa(size_t l);
void	ft_print_nbr_u(unsigned int u);
int		ft_len_ptr_hexa(size_t l);
int		ft_len_nbr(int n);
int		ft_len_nbr_u(unsigned int u);
void	format_c(va_list ap, int *ptr);
void	format_s(va_list ap, int *ptr);
void	format_p(va_list ap, int *ptr);
void	format_di(va_list ap, int *ptr);
void	format_u(va_list ap, int *ptr);
void	format_x(va_list ap, int *ptr);
void	format_upper_x(va_list ap, int *ptr);

#endif
