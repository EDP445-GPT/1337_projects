/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:36:29 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/18 21:57:26 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	*open_fd(void)
{
	struct stat	info;
	static int	i;
	char		*res;
	int			*fd;
	char		*ptr;

	ptr = ft_strjoin("", "/tmp/herdoc");
	fd = malloc(sizeof(int) * 2);
	while (1)
	{
		if (stat(ptr, &info) == 0)
		{
			free(ptr);
			res = ft_itoa(i);
			ptr = ft_strjoin("/tmp/herdoc", res);
			free(res);
		}
		else
			break ;
		i++;
	}
	fd[0] = open(ptr, O_CREAT | O_RDWR, 0644);
	fd[1] = open(ptr, O_RDWR, 0644);
	free(ptr);
	return (fd);
}

int	delimiter_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}
