/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:31:14 by mmaarafi          #+#    #+#             */
/*   Updated: 2024/12/14 22:48:39 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	fun2(va_list ptr, char format)
{
	int	val;

	val = 0;
	if (format == 'c')
		val = val + ft_putchar((char)va_arg(ptr, int));
	else if (format == 's')
		val = val + ft_putstr(va_arg(ptr, char *));
	else if (format == 'p')
	{
		val = val + ft_putstr("0x");
		val = val + fun(va_arg(ptr, unsigned long), "0123456789abcdef");
	}
	else if (format == 'd' || format == 'i')
		val = val + fun1(va_arg(ptr, int));
	else if (format == 'u')
		val = val + fun1((unsigned int)va_arg(ptr, int));
	else if (format == 'x')
		val = val + fun(va_arg(ptr, unsigned int), "0123456789abcdef");
	else if (format == 'X')
		val = val + fun(va_arg(ptr, unsigned int), "0123456789ABCDEF");
	else if (format == '%')
		val = val + ft_putchar('%');
	return (val);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		i;
	int		val;

	if (write(1, 0, 0) == -1)
		return (-1);
	i = 0;
	val = 0;
	va_start(arg, format);
	while (format[i])
	{
		if (format[i] != '%')
		{
			ft_putchar(format[i++]);
			val++;
		}
		else
		{
			if (format[i + 1] != 0)
				val += fun2(arg, format[++i]);
			i++;
		}
	}
	return (va_end(arg), val);
}
