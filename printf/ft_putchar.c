/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:19:27 by mmaarafi          #+#    #+#             */
/*   Updated: 2024/12/11 13:30:29 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	int	returned_value;

	returned_value = write(1, &c, 1);
	if (returned_value == -1)
		return (0);
	return (returned_value);
}
