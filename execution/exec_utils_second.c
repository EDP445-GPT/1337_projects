/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_second.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:15:21 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/18 16:02:16 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	check_for_exit(int status, t_env_copy *env)
{
	if (WIFEXITED(status))
		set_exit_status(env, WEXITSTATUS(status));
	else
		set_exit_status(env, 0);
}

void	check_execverr(t_command **cmd, int i, t_env_copy *env,
				char *command)
{
	struct stat	dir;
	
	free(command);
	stat(cmd[i]->args[0], &dir);
	if (S_ISDIR(dir.st_mode) && ft_strchr(cmd[i]->args[0], '/'))
		print_is_dir(cmd[i]->args[0]);
	else if (!ft_strcmp(cmd[i]->args[0], "..") 
		&& !ft_strchr(cmd[i]->args[0], '/'))
		cmd_not_found(env, cmd, i);
	else
		print_execution_err(cmd[i]->args[0], strerror(errno));
	if (errno == ENOENT)
	{
		update_environment(env, "?", "127");
		free_cmd_env(cmd, env);
		exit(127);
	}
	else
	{
		update_environment(env, "?", "126");
		free_cmd_env(cmd, env);
		exit(126);
	}
}

void	cmd_not_found(t_env_copy *env, t_command **cmd, int i)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd[i]->args[0], 2);
	ft_putstr_fd(":command not found\n", 2);
	update_environment(env, "?", "127");
	free_env(env);
	free_cmd(cmd);
	exit(127);
}

char	*check_cmd_path(t_command **cmd, t_env_copy *env, int i, char *path)
{
	char	*command;

	if ((cmd[i]->args) && (cmd[i]->args[0]) && !is_builtin(cmd[i]->args[0]))
	{
		if (ft_strchr(cmd[i]->args[0], '/'))
			command = ft_strdup(cmd[i]->args[0]);
		else
			command = check_valid_path(path, cmd[i]->args[0]);
		if (!command)
			cmd_not_found(env, cmd, i);
		return (command);
	}
	return (cmd[i]->args[0]);
}

int	cmd_hard_coded(t_command **cmd, t_env_copy *env)
{
	if (cmd[0] && (!cmd[0]->args || !cmd[0]->args[0]) 
		&& (!cmd[0]->redirctions || !cmd[0]->redirctions[0]) 
		&& !cmd[1])
		return (0);
	else if (cmd[0] && (!cmd[0]->args || (cmd[0]->args[0] 
				&& cmd[0]->args[0][0] == '\0')) 
			&& (!cmd[0]->redirctions || !cmd[0]->redirctions[0]) && !cmd[1])
	{
		ft_putstr_fd("bash: : command not found\n", 2);
		update_environment(env, "?", "127");
		return (0);
	}
	else if (cmd[0] && (!cmd[0]->args || (cmd[0]->args[0]
				&& cmd[0]->args[0][0] == '.' && cmd[0]->args[0][1] == '\0')) 
			&& (!cmd[0]->redirctions || !cmd[0]->redirctions[0]) && !cmd[1])
	{
		print_filename_argerr(cmd);
		update_environment(env, "?", "2");
		return (0);
	}
	return (1);
}
