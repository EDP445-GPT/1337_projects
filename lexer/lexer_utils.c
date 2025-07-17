/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:03:57 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/07/14 21:08:19 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	is_redirection_token(char *token)
{
	return (ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<") == 0 || 
		ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0);
}

int	is_pipe_token(char *token)
{
	return (ft_strcmp(token, "|") == 0);
}

int	is_special_token(char *token)
{
	return (is_pipe_token(token) || is_redirection_token(token));
}

int	is_only_space(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_quotes(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			c = str[i];
			i++;
			while (str[i] != c && str[i])
				i++;
			if (!str[i])
				return (0);
		}
		i++;
	}
	return (1);
}
