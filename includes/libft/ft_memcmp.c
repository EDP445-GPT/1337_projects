/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:53:38 by mmaarafi          #+#    #+#             */
/*   Updated: 2024/11/17 22:46:52 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p_s1;
	unsigned char	*p_s2;
	size_t			i;

	p_s1 = (unsigned char *)s1;
	p_s2 = (unsigned char *)s2;
	i = 0;
	if (n > 0)
	{
		n = n - 1;
		while (i <= n)
		{
			if (p_s1[i] == p_s2[i])
				i++;
			else
			{
				return ((unsigned char)p_s1[i] - (unsigned char)p_s2[i]);
				break ;
			}
		}
	}
	return (0);
}
