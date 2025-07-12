// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   custom_split.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/10/30 15:18:43 by mmaarafi          #+#    #+#             */
// /*   Updated: 2025/05/31 11:17:30 by codespace        ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "header.h"

static int redics_pipes(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

static int count_tokens(const char *str)
{
	int i = 0;
	int count = 0;
	int single_qoute = 0;
	int double_qoute = 0;

	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break;

		if (!single_qoute && !double_qoute &&
			((str[i] == '>' && str[i + 1] == '>') ||
			 (str[i] == '<' && str[i + 1] == '<')))
		{
			count++;
			i += 2;
			continue;
		}

		if (!single_qoute && !double_qoute && redics_pipes(str[i]))
		{
			count++;
			i++;
			continue;
		}

		count++;
		while (str[i])
		{
			if (str[i] == '\'' && !double_qoute)
				single_qoute = !single_qoute;
			else if (str[i] == '"' && !single_qoute)
				double_qoute = !double_qoute;

			if (!single_qoute && !double_qoute &&
				(redics_pipes(str[i]) || str[i] == ' '))
				break;
			i++;
		}
	}
	return (count);
}

static void *free_all(char **strs, int k)
{
	while (k-- > 0)
		free(strs[k]);
	free(strs);
	return (NULL);
}

static void *allocate_args(const char *str, int count, char **strs)
{
	int i = 0;
	int k = 0;
	int start;
	int single_qoute = 0;
	int double_qoute = 0;

	while (str[i] && k < count)
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break;
		if (!single_qoute && !double_qoute &&
			((str[i] == '>' && str[i + 1] == '>') ||
			 (str[i] == '<' && str[i + 1] == '<')))
		{
			strs[k++] = ft_substr(str, i, 2);
			i += 2;
			continue;
		}
		if (!single_qoute && !double_qoute && redics_pipes(str[i]))
		{
			strs[k++] = ft_substr(str, i, 1);
			i++;
			continue;
		}
		start = i;
		while (str[i])
		{
			if (str[i] == '\'' && !double_qoute)
				single_qoute = !single_qoute;
			else if (str[i] == '"' && !single_qoute)
				double_qoute = !double_qoute;

			if (!single_qoute && !double_qoute &&
				(redics_pipes(str[i]) || str[i] == ' '))
				break;
			i++;
		}
		strs[k++] = ft_substr(str, start, i - start);
	}
	strs[k] = NULL;
	if (k != count)
		return free_all(strs, k);
	return ((void *)1);
}

char **custom_split_h(const char *s)
{
	char    **strs;
	int     count;

	if (!s)
		return (NULL);
	count = count_tokens(s);
	strs = malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (NULL);
	if (!allocate_args(s, count, strs))
		return (NULL);
	return (strs);
}

int main()
{
   printf("%d\n", custom_split_h("hello>><myname \"this is >\"  \">>file\""));
}
