/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_second.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:57:07 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/17 13:26:46 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	handle_word_token(t_command **cmd, t_parse *pr, t_tokens *tokens)
{
	if (tokens->type == TOKEN_WORD || tokens->type == TOKEN_SINGLE_QUOTE 
		|| tokens->type == TOKEN_DOUBLE_QUOTE)
		cmd[pr->j]->args[0] = ft_strdup(tokens->value);
}

t_tokens	*handle_input_redirect(t_command **cmd, t_parse *pr,
						t_tokens *tokens)
{
	cmd[pr->j]->redirctions[pr->k]->type = IN;
	handle_redirs_file(cmd, pr, tokens->next->value);
	tokens = tokens->next;
	pr->k++;
	return (tokens);
}

t_tokens	*handle_output_redirect(t_command **cmd, t_parse *pr,
							t_tokens *tokens)
{
	cmd[pr->j]->redirctions[pr->k]->type = OUT;
	handle_redirs_file(cmd, pr, tokens->next->value);
	tokens = tokens->next;
	pr->k++;
	return (tokens);
}

t_tokens	*handle_heredoc_token(t_command **cmd, t_parse *pr,
							t_tokens *tokens)
{
	cmd[pr->j]->redirctions[pr->k]->type = HEREDOC;
	handle_herdoc_delimiter(cmd, pr, tokens->next->value);
	tokens = tokens->next;
	pr->k++;
	return (tokens);
}

t_tokens	*handle_append_redirect(t_command **cmd, t_parse *pr,
							t_tokens *tokens)
{
	cmd[pr->j]->redirctions[pr->k]->type = APPEND;
	handle_redirs_file(cmd, pr, tokens->next->value);
	tokens = tokens->next;
	pr->k++;
	return (tokens);
}
