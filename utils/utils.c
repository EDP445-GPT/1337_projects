/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:13:43 by codespace         #+#    #+#             */
/*   Updated: 2025/07/14 13:09:22 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*ft_strdup_name(char *src)
{
	int		length;
	int		i;
	char	*p;

	length = 0;
	while (src[length] != '=')
		length++;
	p = malloc(length + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '=')
	{
		p[i] = src[i];
		i++;
	}
	p[i] = 0;
	return (p);
}

char	*ft_strdup_value(char *src)
{
	int		length;
	int		i;
	char	*p;

	length = 0;
	while (src[length] != '=')
		length++;
	src = src + length + 1;
	length = strlen(src);
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
