/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 09:56:01 by csubires          #+#    #+#             */
/*   Updated: 2024/06/04 18:26:20 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_parse_args(char c, va_list va)
{
	char	*str_hex_lo;
	char	*str_hex_up;

	str_hex_lo = "0123456789abcdef";
	str_hex_up = "0123456789ABCDEF";
	if (c == 'c')
		return (ft_putchar_fd(va_arg(va, int), 1));
	else if (c == '%')
		return (ft_putchar_fd('%', 1));
	else if (c == 's')
		return (ft_putstr_fd(va_arg(va, char *), 1));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(va, int), 1));
	else if (c == 'p')
		return (ft_putnbr_base(c, va_arg(va, unsigned long), str_hex_lo));
	else if (c == 'u')
		return (ft_putnbr_base(c, va_arg(va, unsigned int), "0123456789"));
	else if (c == 'x')
		return (ft_putnbr_base(c, va_arg(va, unsigned int), str_hex_lo));
	else if (c == 'X')
		return (ft_putnbr_base(c, va_arg(va, unsigned int), str_hex_up));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	long	total_print;
	long	tmp_res;

	va_start(args, s);
	total_print = 0;
	while (*s)
	{
		if (s[0] == '%' && s[1])
		{
			tmp_res = ft_parse_args(s[1], args);
			s++;
		}
		else
			tmp_res = ft_putchar_fd(s[0], 1);
		if (tmp_res == -1)
			return (-1);
		total_print += tmp_res;
		s++;
	}
	va_end(args);
	return (total_print);
}
