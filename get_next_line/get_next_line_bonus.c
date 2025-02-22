/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:08:15 by mmaarafi          #+#    #+#             */
/*   Updated: 2024/12/16 17:44:01 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	find_start(const char *s1)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != '\n')
		{
			i++;
			continue ;
		}
		else
			break ;
	}
	if (ft_strlen(s1) != i)
		return (i + 1);
	return (i);
}

char	*returned_line(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		length;
	int		i;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = find_start(s1);
	length = end - start;
	ptr = malloc(length + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (start < end)
		ptr[i++] = s1[start++];
	ptr[i] = 0;
	return (ptr);
}

char	*read_line(char *stash, int buffer_size, int fd)
{
	char	*buffer;
	int		read_return ;

	buffer = malloc(buffer_size + 1);
	if (!buffer)
		return (free(stash), NULL);
	read_return = 1;
	while (!ft_strchr(stash, '\n') && read_return != 0)
	{
		read_return = read(fd, buffer, BUFFER_SIZE);
		if (read_return == -1)
		{
			if (stash)
				free(stash);
			free(buffer);
			return (NULL);
		}
		if (read_return == 0)
			break ;
		buffer[read_return] = 0;
		stash = ft_strjoin(stash, buffer);
	}
	return (free(buffer), stash);
}

char	*fun(char **stash, char *line)
{
	int		start;
	char	*tmp;

	if (ft_strchr(*stash, '\n'))
	{
		start = find_start(*stash);
		tmp = *stash;
		*stash = ft_strdup(*stash + start);
		free(tmp);
		if (!*stash)
			return (free(line), NULL);
		if (*(*stash) == 0)
		{
			free(*stash);
			*stash = NULL;
		}
	}
	else
	{
		free(*stash);
		*stash = NULL;
	}
	return ("");
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*tmp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_line(stash[fd], BUFFER_SIZE, fd);
	if (!stash[fd])
		return (NULL);
	line = returned_line(stash[fd], "\n");
	if (!line)
	{
		if (stash[fd])
		{
			free(stash[fd]);
			stash[fd] = NULL;
		}
		return (NULL);
	}
	tmp = fun(&stash[fd], line);
	if (!tmp)
		return (NULL);
	return (line);
}
