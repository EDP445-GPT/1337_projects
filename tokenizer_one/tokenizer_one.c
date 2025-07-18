/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:45:13 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/07/14 13:06:10 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	is_word(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		return (0);
	return (1);
}

int	is_single_q(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	is_double_q(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

static int	get_token_type(char *arg)
{
	if (is_word(arg))
	{
		if (is_single_q(arg))
			return (TOKEN_SINGLE_QUOTE);
		if (is_double_q(arg))
			return (TOKEN_DOUBLE_QUOTE);
		return (TOKEN_WORD);
	}
	if (is_pipe(arg))
		return (TOKEN_PIPE);
	if (is_redirect_in(arg))
		return (TOKEN_REDIRECT_IN);
	if (is_redirect_out(arg))
		return (TOKEN_REDIRECT_OUT);
	if (is_heredoc(arg))
		return (TOKEN_HEREDOC);
	if (is_append_out(arg))
		return (TOKEN_APPEND_OUT);
	return (-1);
}

t_tokens	*tokenizer(char *str)
{
	t_tokens	*tokens;
	char		**args;
	int			i;
	int			type;

	i = 0;
	tokens = NULL;
	args = custom_split(str);
	while (args[i])
	{
		type = get_token_type(args[i]);
		if (type != -1)
			add_to_list(&tokens, type, args[i]);
		i++;
	}
	free_envp_array(args); // change here
	return (tokens);
}
