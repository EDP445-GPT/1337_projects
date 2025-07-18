/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_one_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:43:28 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/07/14 13:04:27 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	is_pipe(char *str)
{
	if (str[0] == '|' && !str[1])
		return (1);
	else
		return (0);
}

int	is_redirect_in(char *str)
{
	if (str[0] == '<' && !str[1])
		return (1);
	else
		return (0);
}

int	is_redirect_out(char *str)
{
	if (str[0] == '>' && !str[1])
		return (1);
	else
		return (0);
}

int	is_heredoc(char *str)
{
	if (str[0] == '<' && str[1] == '<' && !str[2])
		return (1);
	else
		return (0);
}

int	is_append_out(char *str)
{
	if (str[0] == '>' && str[1] == '>' && !str[2])
		return (1);
	else
		return (0);
}
