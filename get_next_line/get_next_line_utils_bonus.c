 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 14:27:03 by mmaarafi          #+#    #+#             */
/*   Updated: 2024/12/09 17:19:12 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strcat(char *dest, const char *src)
{
	int	length_dest;
	int	i;

	i = 0;
	length_dest = ft_strlen(dest);
	while (src[i] != '\0')
	{
		dest[length_dest + i] = src[i];
		i++;
	}
	dest[length_dest + i] = '\0';
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	int		length;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char *stash, char *buffer)
{
	int		length;
	char	*str;

	if (!stash && !buffer)
		return (NULL);
	if (!stash)
		return (ft_strdup(buffer));
	if (!buffer)
		return (ft_strdup(stash));
	length = ft_strlen(stash) + ft_strlen(buffer);
	str = malloc(length + 1);
	if (str == NULL)
		return (free(stash), NULL);
	str[0] = '\0';
	ft_strcat(str, stash);
	ft_strcat(str, buffer);
	free(stash);
	return (str);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	int		length;
	int		i;
	char	*p;

	if (!src)
		return (NULL);
	length = ft_strlen(src);
	p = malloc(length + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		p[i] = src[i];
		i++;
	}
	p[i] = 0;
	return (p);
}
