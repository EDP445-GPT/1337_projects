/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:48:59 by mmaarafi          #+#    #+#             */
/*   Updated: 2024/11/17 20:40:36 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dest;
	char	*source;
	size_t	i;

	if (!dst && !src)
		return (dst);
	dest = (char *)dst;
	source = (char *)src;
	if (dest > source)
	{
		while (len--)
			dest[len] = source[len];
		return (dest);
	}
	i = 0;
	while (i < len)
	{
		dest[i] = source[i];
		i++;
	}
	return (dest);
}
