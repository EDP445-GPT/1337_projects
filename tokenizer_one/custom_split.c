/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:45:13 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/07/18 17:55:41 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

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

static int	handle_special_operators(const char *str, 
	int *i, int k, char **strs)
{
	if ((str[*i] == '>' && str[*i + 1] == '>') || 
		(str[*i] == '<' && str[*i + 1] == '<'))
	{
		if (str[*i] == '>')
			strs[k] = ft_strdup(">>");
		if (str[*i] == '<')
			strs[k] = ft_strdup("<<");
		*i += 2;
		return (1);
	}
	if (str[*i] == '|')
		strs[k] = ft_strdup("|");
	else if (str[*i] == '>')
		strs[k] = ft_strdup(">");
	else if (str[*i] == '<')
		strs[k] = ft_strdup("<");
	(*i)++;
	return (1);
}

static void	*allocate_token(const char *str, int end, int *jk, char **strs)
{
	int	len;
	int	l;

	len = end - jk[0];
	l = 0;
	strs[jk[1]] = malloc(len + 1);
	if (strs[jk[1]] == NULL)
		return (free_all(strs, jk[1]));
	while (jk[0] < end)
		strs[jk[1]][l++] = str[jk[0]++];
	strs[jk[1]][l] = 0;
	return ((void *)1);
}

static void	*allocate_duplicate(const char *str, int count, char **strs)
{
	int	i;
	int	jk[2];
	int	single_quote;
	int	double_quote;

	i = 0;
	jk[1] = 0;
	single_quote = 0;
	double_quote = 0;
	while (jk[1] < count)
	{
		if ((!single_quote && !double_quote) && inside_charset(str[i]))
		{
			handle_special_operators(str, &i, jk[1], strs);
			jk[1]++;
			continue ;
		}
		jk[0] = i;
		i = find_token_end(str, i, &single_quote, &double_quote);
		if (allocate_token(str, i, jk, strs) != (void *)1)
			return (NULL);
		jk[1]++;
	}
	strs[jk[1]] = NULL;
	return ((void *)1);
}

char	**custom_split(char const *s)
{
	char	**strs;
	int		count;

	if (!s)
		return (NULL);
	count = count_words(s);
	strs = malloc(sizeof(char *) * (count + 1));
	if (strs == NULL)
		return (NULL);
	if (!allocate_duplicate(s, count, strs))
		return (NULL);
	return (strs);
}