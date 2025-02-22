/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:18:43 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/02/06 17:22:13 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	my_count_words(const char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;
			continue ;
		}
		while (str[i] && !(str[i] == c))
			i++;
		count++;
	}
	return (count);
}

static void	*free_all(char **strs, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static void	*allocate_duplicate(const char *str, char c, int count, char **strs)
{
	int	i;
	int	j;
	int	k;
	int	l;

	l = 0;
	k = 0;
	i = 0;
	while (k < count)
	{
		while (str[i] == c)
			i++;
		j = i;
		while (str[i] && !(str[i] == c))
			i++;
		strs[k] = malloc((i - j) + 1);
		if (strs[k] == NULL)
			return (free_all(strs, k));
		while (j < i)
			strs[k][l++] = str[j++];
		strs[k++][l] = 0;
		l = 0;
	}
	strs[k] = NULL;
	return ((void *)1);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		count;

	if (!s)
		return (NULL);
	count = my_count_words(s, c);
	strs = malloc(sizeof(char *) * (count + 1));
	if (strs == NULL)
		return (NULL);
	if (!allocate_duplicate(s, c, count, strs))
		return (NULL);
	return (strs);
}
