/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_Redirs_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:53:08 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/17 18:29:30 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	find_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == '\'' || str[i] == '\"'))
		i++;
	if (str[i] == '$')
		return (1);
	return (0);
}

void	handle_param_after_file(t_command **cmd, t_parse *pr, char **arguments)
{
	int	i;

	i = 1;
	while (arguments[i])
	{
		if (cmd[pr->j]->args[0] == NULL)
		{
			cmd[pr->j]->args[0] = ft_strdup(arguments[i]);
			i++;
			continue ;
		}
		cmd[pr->j]->args[0] = ft_strjoin(cmd[pr->j]->args[0], " ");
		cmd[pr->j]->args[0] = ft_strjoin(cmd[pr->j]->args[0], arguments[i]);
		i++;
	}
}

void	handle_redirs_file(t_command **cmd, t_parse *pr, char *s)
{
	char	**args;
	char	**res;

	args = ft_split_args_file_qoute(s);
	cmd[pr->j]->redirctions[pr->k]->file = ft_strdup(args[0]);
	if (find_expand(args[0]))
	{
		cmd[pr->j]->redirctions[pr->k]->file = ft_expand(args[0], pr->env);
		res = ft_split_args(cmd[pr->j]->redirctions[pr->k]->file, pr->env);
		if (res[1] || !res[0])
		{
			write(2, "ambiguous redirect\n", 20);
			update_environment(pr->env, "?", "1");
		}
		cmd[pr->j]->redirctions[pr->k]->file = res[0];
	}
	else
		cmd[pr->j]->redirctions[pr->k]->file = 
			skip_qoute(cmd[pr->j]->redirctions[pr->k]->file);
	if (args[1])
		handle_param_after_file(cmd, pr, args);
}

void	handle_param_after_herdoc(t_command **cmd, t_parse *pr,
							char **arguments)
{
	int	i;

	i = 1;
	while (arguments[i])
	{
		if (cmd[pr->j]->args[0] == NULL)
		{
			cmd[pr->j]->args[0] = ft_strdup(arguments[i]);
			i++;
			continue ;
		}
		cmd[pr->j]->args[0] = ft_strjoin(cmd[pr->j]->args[0], " ");
		cmd[pr->j]->args[0] = ft_strjoin(cmd[pr->j]->args[0], arguments[i]);
		i++;
	}
}

void	handle_herdoc_delimiter(t_command **cmd, t_parse *pr, char *s)
{
	char	**args;

	args = ft_split_args_file_qoute(s);
	cmd[pr->j]->redirctions[pr->k]->file = ft_strdup(args[0]);
	args = ft_split_args_file(s);
	if (args[1])
		handle_param_after_herdoc(cmd, pr, args);
}
