/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:30:01 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/07/15 21:08:33 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	free_tokens(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}  

int	check_pipes(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_pipe_token(tokens[i]))
		{
			if ((i - 1) < 0)
				return (stder("syntax error near unexpected token `|'\n", 2), 0);
			if (!tokens[i + 1])
				return (stder("syntax error near unexpected token `newline'\n"
						, 2)
					, 0);
			if (is_pipe_token(tokens[i + 1]))
				return (stder("syntax error near unexpected token `||'\n", 2)
					, 0);
			if (((i - 1) >= 0 && !tokens[i - 1]) && 
				is_redirection_token(tokens[i + 1]))
				return (stder("syntax error near unexpected token `", 2),
					stder(tokens[i + 1], 2), stder("'\n", 2), 0);
		}
		i++;
	}
	return (1);
}

int	redirection_syntax_error(char **tokens, int i)
{
	if (!tokens[i + 1])
		return (stder("syntax error near unexpected token `newline'\n", 2) 
			, 0);
	if (is_pipe_token(tokens[i + 1]))
		return (stder("syntax error near unexpected token `|'\n", 2)
			, 0);
	if (is_redirection_token(tokens[i + 1]))
		return (stder("syntax error near unexpected token `", 2), 
			stder(tokens[i + 1], 2), stder("'\n", 2), 0);
	if (is_only_space(tokens[i + 1]))
		return (stder("syntax error near unexpected token `", 2),
			stder(tokens[i + 2], 2), stder("'\n", 2), 0);
	return (1);
}

int	check_redirections(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_redirection_token(tokens[i]))
		{
			if (!redirection_syntax_error(tokens, i))
				return (0);
		}
		if (ft_strcmp(tokens[i], ">") == 0 && 
			tokens[i + 1] && ft_strcmp(tokens[i + 1], ">") == 0)
			return (stder("syntax error near unexpected token `>'\n", 2), 0);
		if (ft_strcmp(tokens[i], "<") == 0 && 
			tokens[i + 1] && ft_strcmp(tokens[i + 1], "<") == 0)
			return (stder("syntax error near unexpected token `<'\n", 2), 0);
		i++;
	}
	return (1);
}

int	lexer(char *str, t_env_copy *env)
{
	char	**tokens;
	int		i;

	i = 0;
	if (!str)
		return (1);
	if (!check_quotes(str))
		return (update_environment(env, "?", "1"),
			stder("syntax error: unclosed quotes\n", 2), 0);
	tokens = lexer_custom_split(str);
	if (!tokens)
		return (update_environment(env, "?", "1"), 0);
	if (!tokens[0])
		return (free_tokens(tokens), 1);
	if (!check_pipes(tokens))
		return (update_environment(env, "?", "258"), free_tokens(tokens), 0);
	if (!check_redirections(tokens))
		return (update_environment(env, "?", "258"), free_tokens(tokens), 0);
	free_tokens(tokens);
	return (1);
}
