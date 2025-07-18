/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:19:22 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/18 19:06:00 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	handle_pipe(int prev_pipe, t_exec *exe, t_command **cmd)
{
	if (prev_pipe != -1)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	if (cmd[exe->i + 1])
	{
		dup2(exe->pipe_fd[1], STDOUT_FILENO);
		close(exe->pipe_fd[1]);
		close(exe->pipe_fd[0]);
	}
}

pid_t	real_execution(t_exec *exe, t_command **cmd, t_env_copy *env)
{
	char	*command;

	if (cmd[exe->i + 1])
		pipe(exe->pipe_fd);
	exe->pid = fork();
	if (exe->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		handle_pipe(exe->prev_pipe, exe, cmd);
		if (cmd[exe->i]->redirctions)
		if (!handle_redirection(cmd[exe->i], env))
			exit(1) ;
		if ((!cmd[exe->i]->args) || (!cmd[exe->i]->args[0]))
			exit(0);
		command = check_cmd_path(cmd, env, exe->i, exe->path);
		if (!mutiple_builtins(cmd, exe->i, env))
			exit(0);
		else
		{
			if (execve(command, cmd[exe->i]->args, exe->envp) == -1)
				check_execverr(cmd, exe->i, env, command);
		}
	}
	return (exe->pid);
}

void	wait_for_child(t_env_copy *env, t_command **cmd, t_exec *exe)
{
	char	*cp;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(exe->pids, &(exe->status), 0);
	if (WIFEXITED(exe->status))
	{
		cp = (ft_get_env_node("?", env)->value);
		(ft_get_env_node("?", env))->value = ft_itoa(WEXITSTATUS(exe->status));
		free(cp);
	}
	while (wait(NULL) > 0)
		;
	signal(SIGINT, signal_handler);
	if (exe->i - 1 >= 0 && cmd[exe->i - 1]->args 
		&& ft_strcmp(cmd[exe->i - 1]->args[0], "exit") == 0)
		check_for_exit(exe->status, env);
	else
	{
		check_exit_type(exe, env);
	}
}

int	handle_pipe_parent(t_command **cmd, t_exec *exe)
{
	if (exe->prev_pipe != -1)
		close(exe->prev_pipe);
	if (cmd[exe->i + 1])
	{
		close(exe->pipe_fd[1]);
		exe->prev_pipe = exe->pipe_fd[0];
	}
	exe->pids = exe->pid;
	return (exe->pids);
}

void	exec_command(t_command **cmd, t_env_copy *env)
{
	t_exec	exe;

	exe.i = ((exe.pids = 0), (exe.prev_pipe = -1), 0);
	if (!cmd_hard_coded(cmd, env))
		return ;
	if (!cmd[1] && !single_builtin(cmd, env))
		return ;
	else
	{
		exe.path = find_path(env);
		exe.envp = struct_to_arr_env(env);
		while (cmd[exe.i])
		{
			exe.pid = real_execution(&exe, cmd, env);
			if (exe.pid > 0)
				exe.pids = handle_pipe_parent(cmd, &exe);
			exe.i++;
		}
		if (exe.pids)
			wait_for_child(env, cmd, &exe);
		free_envp_array(exe.envp);
	}
}
