/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:35:42 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/17 13:42:54 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	fd_error(int fd, t_env_copy *env, t_command *cmd, int i)
{
	if (fd < 0)
	{
		perror(cmd->redirctions[i]->file);
		update_environment(env, "?", "1");
		exit(1);
	}
}

void	redirs_in(t_env_copy *env, t_command *cmd, int i)
{
	int	fd;

	fd = open(cmd->redirctions[i]->file, O_RDONLY);
	fd_error(fd, env, cmd, i);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redirs_out(t_env_copy *env, t_command *cmd, int i)
{
	int	fd;

	fd = open(cmd->redirctions[i]->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	fd_error(fd, env, cmd, i);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redirs_append(t_env_copy *env, t_command *cmd, int i)
{
	int	fd;

	fd = open(cmd->redirctions[i]->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	fd_error(fd, env, cmd, i);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_redirection(t_command *cmd, t_env_copy *env)
{
	int	i;
	int	fd_herd;

	i = 0;
	while (cmd->redirctions[i])
	{
		if (cmd->redirctions[i]->type == IN)
			redirs_in(env, cmd, i);
		else if (cmd->redirctions[i]->type == OUT)
			redirs_out(env, cmd, i);
		else if (cmd->redirctions[i]->type == APPEND)
			redirs_append(env, cmd, i);
		else if (cmd->redirctions[i]->type == HEREDOC)
		{
			fd_herd = cmd->redirctions[i]->fd_heredoc;
			dup2(fd_herd, STDIN_FILENO);
			close(fd_herd);
		}
		i++;
	}
}
