/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocating_parser_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:01:30 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/17 13:23:10 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	c_count(t_tokens *tokens)
{
	int	i;

	i = 1;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
			i++;
		tokens = tokens->next;
	}
	return (i);
}

t_command	**c_alocate(t_tokens *p)
{
	int			i;
	t_command	**cmd;
	int			v;

	v = -1;
	i = 1;
	i = c_count(p);
	cmd = malloc(sizeof(t_command *) * (i + 1));
	while (++v < i)
		cmd[v] = malloc(sizeof(t_command));
	cmd[v] = NULL;
	if (!cmd)
		return (perror("malloc failed"), NULL);
	return (cmd);
}

int	count_args(t_tokens *tmp)
{
	int	args_count;

	args_count = 0;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (tmp->type == TOKEN_WORD || tmp->type == TOKEN_SINGLE_QUOTE)
			args_count++;
		tmp = tmp->next;
	}
	return (args_count);
}

int	c_redic(t_tokens *tmp)
{
	int	redirs;

	redirs = 0;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (tmp->type == TOKEN_REDIRECT_IN || tmp->type == TOKEN_REDIRECT_OUT 
			|| tmp->type == TOKEN_HEREDOC || tmp->type == TOKEN_APPEND_OUT)
			redirs++;
		tmp = tmp->next;
	}
	return (redirs);
}
