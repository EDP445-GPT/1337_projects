/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:20:54 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/17 13:25:58 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_tokens	*process_token(t_command **cmd, t_parse *pr, t_tokens *tokens)
{
	if (tokens->type == TOKEN_WORD || tokens->type == TOKEN_SINGLE_QUOTE 
		|| tokens->type == TOKEN_DOUBLE_QUOTE)
		handle_word_token(cmd, pr, tokens);
	else if (tokens->type == TOKEN_REDIRECT_IN)
		tokens = handle_input_redirect(cmd, pr, tokens);
	else if (tokens->type == TOKEN_REDIRECT_OUT)
		tokens = handle_output_redirect(cmd, pr, tokens);
	else if (tokens->type == TOKEN_HEREDOC)
		tokens = handle_heredoc_token(cmd, pr, tokens);
	else if (tokens->type == TOKEN_APPEND_OUT)
		tokens = handle_append_redirect(cmd, pr, tokens);
	return (tokens);
}

t_tokens	*handle_pipe_token(t_command **cmd, t_parse *pr, t_tokens *tokens)
{
	cmd[pr->j]->args = ft_split_args(cmd[pr->j]->args[0], pr->env);
	cmd[pr->j]->redirctions[pr->k] = NULL;
	tokens = tokens->next;
	pr->k = 0;
	pr->i = 0;
	pr->j++;
	return (tokens);
}

t_tokens	*process_command_tokens(t_command **cmd, t_parse *pr,
							t_tokens *tokens)
{
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		tokens = process_token(cmd, pr, tokens);
		tokens = tokens->next;
	}
	return (tokens);
}

void	init_parser(t_parse *pr, t_env_copy *p)
{
	pr->j = 0;
	pr->k = 0;
	pr->env = p;
}

void	finalize_last_command(t_command **cmd, t_parse *pr)
{
	cmd[pr->j]->redirctions[pr->k] = NULL;
	pr->k = 0;
	if (cmd[pr->j]->args[0])
		cmd[pr->j]->args = ft_split_args(cmd[pr->j]->args[0], pr->env);
}
