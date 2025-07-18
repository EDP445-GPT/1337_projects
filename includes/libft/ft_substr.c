/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:21:01 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/07/18 15:55:19 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	unsigned int	s_size;
	char			*p;
	int				length;

	if (!s)
		return (NULL);
	s_size = ft_strlen(s);
	if (start >= s_size)
		return (ft_strdup(""));
	length = s_size - start;
	if (s_size - start > len)
		length = len;
	p = malloc(length + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}

char	*ft_substr_expand(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	unsigned int	s_size;
	char			*p;
	int				length;

	if (!s)
		return (ft_strdup(""));
	s_size = ft_strlen(s);
	if (start >= s_size)
		return (ft_strdup(""));
	length = s_size - start;
	if (s_size - start > len)
		length = len;
	p = malloc(length + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}
