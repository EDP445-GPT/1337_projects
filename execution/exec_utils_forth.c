/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_forth.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 11:16:16 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/18 16:27:30 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	print_execution_err(char *s, char *str)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void	print_is_dir(char *s)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": is a directory\n", 2);
}

void	check_exit_type(t_exec *exe, t_env_copy *env)
{
	if (WIFEXITED(exe->status))
		set_exit_status(env, WEXITSTATUS(exe->status));
	else if (WIFSIGNALED(exe->status))
	{
		printf("\n");
		if (WTERMSIG(exe->status) == SIGINT)
			set_exit_status(env, 130);
		if (WTERMSIG(exe->status) == SIGQUIT)
			set_exit_status(env, 131);
		if (WTERMSIG(exe->status) == SIGPIPE)
			set_exit_status(env, 1);
	}
}

void	print_filename_argerr(t_command **cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd[0]->args[0], 2);
	ft_putstr_fd(": filename argument required\n", 2);
	ft_putstr_fd(cmd[0]->args[0], 2);
	ft_putstr_fd(": usage: ", 2);
	ft_putstr_fd(cmd[0]->args[0], 2);
	ft_putstr_fd(" filename [arguments]\n", 2);
}

void	free_cmd(t_command **cmd)
{
	int	i;
	int	j;

	if (!cmd)
		return;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i]->args)
		{
			j = 0;
			while (cmd[i]->args[j])
			{
				free(cmd[i]->args[j]);
				j++;
			}
			free(cmd[i]->args);
		}
		if (cmd[i]->redirctions)
		{
			j = 0;
			while (cmd[i]->redirctions[j])
			{
				free(cmd[i]->redirctions[j]->file); // change here
				free(cmd[i]->redirctions[j]);
				j++;
			}
			free(cmd[i]->redirctions);
		}
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

