/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:18:13 by mmaarafi          #+#    #+#             */
/*   Updated: 2024/11/15 10:34:50 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

static int	inside_set(const char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	find_start(const char *s1, const char *set)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (inside_set(s1[i], set))
		{
			i++;
			continue ;
		}
		else
			break ;
	}
	return (i);
}

static int	find_end(const char *s1, const char *set)
{
	int	length;

	length = ft_strlen(s1) - 1;
	while (length != -1)
	{
		if (inside_set(s1[length], set))
		{
			length--;
			continue ;
		}
		else
			break ;
	}
	return (length);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		length;
	int		i;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	start = find_start(s1, set);
	end = find_end(s1, set);
	length = end - start + 2;
	if (start > end)
		return (ft_strdup(""));
	ptr = malloc(length);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (start <= end)
		ptr[i++] = s1[start++];
	ptr[i] = 0;
	return (ptr);
}
