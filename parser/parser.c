/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:01:06 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/18 21:45:30 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_command	**cmd_allocation(t_tokens *tokens)
{
	int			cmd_count;
	t_tokens	*tmp;
	int			g;
	int			i;
	t_command	**cmd;

	cmd_count = ((tmp = tokens),
			(cmd = c_alocate(tokens)), (i = 0), c_count(tokens));
	while (i < cmd_count)
	{
		if (tmp->type == TOKEN_PIPE)
			tmp = tmp->next;
		cmd[i]->args = malloc(sizeof(char *) * (count_args(tmp) + 1));
		g = 0;
		while (g < count_args(tmp) + 1)
			cmd[i]->args[g++] = NULL;
		cmd[i]->redirctions = malloc(sizeof(t_redic *) * (c_redic(tmp) + 1));
		g = 0;
		while (g < c_redic(tmp))
			cmd[i]->redirctions[g++] = malloc(sizeof(t_redic));
		while (tmp && tmp->type != TOKEN_PIPE)
			tmp = tmp->next;
		i++;
	}
	return (cmd);
}

void	ft_parser(t_tokens *tokens, t_env_copy *p)
{
	t_command	**cmd;
	t_parse		*pr;
	t_parse		pr_data;
	t_tokens	*tmp; //change here

	tmp = tokens; // change here
	pr = &pr_data;
	init_parser(pr, p);
	if (!tokens)
		return ;
	cmd = cmd_allocation(tokens);
	while (tokens)
	{
		tokens = process_command_tokens(cmd, pr, tokens);
		if (tokens && tokens->type == TOKEN_PIPE)
			tokens = handle_pipe_token(cmd, pr, tokens);
	}
	finalize_last_command(cmd, pr);
	free_tokens_list(tmp); // change here this function use to free tokens after the while loop which become null
	if (heredoc(cmd, p))
		exec_command(cmd, p);
	free_cmd(cmd);
}
