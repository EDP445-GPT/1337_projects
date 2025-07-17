#include "../header.h"

int is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"));
}

char **struct_to_arr_env(t_env_copy *env)
{
	int i;
	char **envp;
	t_env_copy *tmp = env;
	char *temp;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	tmp = env;

	i = 0;
	while (tmp)
	{
		temp = ft_strjoin(tmp->name, "=");
		envp[i] = ft_strjoin(temp, tmp->value);
		free(temp);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

t_env_copy *ft_get_env_node(char *name, t_env_copy *env)
{
	while (env)
	{
		if (ft_strcmp(name, env->name) == 0)
			return (env);
		env = env->next;
	}
	return NULL;
}

int cmd_hard_coded(t_command **cmd, t_env_copy *env)
{
	if (cmd[0] && (!cmd[0]->args || !cmd[0]->args[0]) &&
		(!cmd[0]->redirctions || !cmd[0]->redirctions[0]) &&
		!cmd[1])
		return (0);
	else if (cmd[0] && (!cmd[0]->args || (cmd[0]->args[0] && cmd[0]->args[0][0] == '\0')) &&
			 (!cmd[0]->redirctions || !cmd[0]->redirctions[0]) && !cmd[1])
	{
		dprintf(2, "bash: : command not found\n");
		update_environment(env, "?", "127");
		return (0);
	}
	else if (cmd[0] && (!cmd[0]->args || (cmd[0]->args[0] && cmd[0]->args[0][0] == '.' && cmd[0]->args[0][1] == '\0')) &&
			 (!cmd[0]->redirctions || !cmd[0]->redirctions[0]) && !cmd[1])
	{
		dprintf(2, "bash: %s: filename argument required\n", cmd[0]->args[0]);
		dprintf(2, "%s: usage: %s: filename [arguments]\n", cmd[0]->args[0], cmd[0]->args[0]);
		update_environment(env, "?", "2");
		return (0);
	}
	return (1);
}

int single_builtin(t_command **cmd, t_env_copy *env)
{
	if (!cmd[1] && ft_strcmp(cmd[0]->args[0], "export") == 0)
		return (ft_export(cmd, env), 0);
	else if (!cmd[1] && ft_strcmp(cmd[0]->args[0], "cd") == 0)
		return (ft_cd(cmd, env), 0);
	else if (!cmd[1] && ft_strcmp(cmd[0]->args[0], "unset") == 0)
		return (ft_unset(env, cmd[0]->args), 0);
	else if (!cmd[1] && ft_strcmp(cmd[0]->args[0], "exit") == 0)
		return (ft_exit(cmd[0]->args, env), 0); // free here
	return (1);
}

int mutiple_builtins(t_command **cmd, int i, t_env_copy *env)
{
	if (ft_strcmp(cmd[i]->args[0], "export") == 0)
		return (ft_export(cmd, env), 0);
	else if ((ft_strcmp(cmd[i]->args[0], "cd") == 0))
		return (ft_cd(cmd, env), 0);
	else if (ft_strcmp(cmd[i]->args[0], "unset") == 0)
		return (ft_unset(env, cmd[0]->args), 0);
	else if (ft_strcmp(cmd[i]->args[0], "exit") == 0)
		return (ft_exit(cmd[i]->args, env), 0);
	else if ((ft_strcmp(cmd[i]->args[0], "pwd") == 0) || (ft_strcmp(cmd[i]->args[0], "PWD") == 0))
		return (ft_pwd(env), 0);
	else if ((ft_strcmp(cmd[i]->args[0], "echo") == 0) || (ft_strcmp(cmd[i]->args[0], "ECHO") == 0))
		return (ft_echo(cmd[i]->args), 0);
	else if ((ft_strcmp(cmd[i]->args[0], "env") == 0) || (ft_strcmp(cmd[i]->args[0], "ENV") == 0))
		return (ft_env(env), 0);
	return (1);
}

char *check_cmd_path(t_command **cmd, t_env_copy *env, int i, char *path)
{
	char *command;

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

void cmd_not_found(t_env_copy *env, t_command **cmd, int i)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd[i]->args[0], 2);
	ft_putstr_fd(":command not found\n", 2);
	update_environment(env, "?", "127");
	exit(127);
}

void check_execverr(t_command **cmd, int i, t_env_copy *env)
{
	struct stat dir;
	stat(cmd[i]->args[0], &dir);
	if (S_ISDIR(dir.st_mode) && ft_strchr(cmd[i]->args[0], '/'))
		dprintf(2, "bash: %s: is a directory\n", cmd[i]->args[0]);
	else if (!ft_strcmp(cmd[i]->args[0], "..") && !ft_strchr(cmd[i]->args[0], '/'))
		cmd_not_found(env, cmd, i);
	else
		dprintf(2, "bash: %s %s\n", cmd[i]->args[0], strerror(errno)); // change to ft_putstr_fd
	if (errno == ENOENT)
	{
		update_environment(env, "?", "127");
		exit(127);
	}
	else
	{
		update_environment(env, "?", "126");
		exit(126);
	}
}
void handle_pipe(int prev_pipe, t_exec *exe, t_command **cmd)
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
pid_t real_execution(t_exec *exe, t_command **cmd, t_env_copy *env, int prev_pipe)
{
	char *command;

	if (cmd[exe->i + 1])
		pipe(exe->pipe_fd);
	exe->pid = fork();
	if (exe->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		handle_pipe(prev_pipe, exe, cmd);
		if (cmd[exe->i]->redirctions)
			handle_redirection(cmd[exe->i], env);
		if ((!cmd[exe->i]->args) || (!cmd[exe->i]->args[0]))
			exit(0);
		command = check_cmd_path(cmd, env, exe->i, exe->path);
		if (!mutiple_builtins(cmd, exe->i, env))
			exit(0);
		else
		{
			if (execve(command, cmd[exe->i]->args, exe->envp) == -1)
				check_execverr(cmd, exe->i, env);
		}
	}
	return (exe->pid);
}

void	check_for_exit(int status, t_env_copy *env)
{
	if (WIFEXITED(status))
		update_environment(env, "?", ft_itoa(WEXITSTATUS(status)));
	else
		update_environment(env, "?", ft_itoa(0));
}

void	wait_for_child(t_env_copy *env, t_command **cmd, t_exec *exe)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(exe->pids, &(exe->status), 0);
	if (WIFEXITED(exe->status))
		(ft_get_env_node("?", env))->value = ft_itoa(WEXITSTATUS(exe->status));
	while (wait(NULL) > 0)
		;
	signal(SIGINT, signal_handler);
	if (exe->i - 1 >= 0 && cmd[exe->i - 1]->args && ft_strcmp(cmd[exe->i - 1]->args[0], "exit") == 0)
		check_for_exit(exe->status, env);
	else
	{
		if (WIFEXITED(exe->status))
			update_environment(env, "?", ft_itoa(WEXITSTATUS(exe->status)));
		else if (WIFSIGNALED(exe->status))
		{
			printf("\n");
			if (WTERMSIG(exe->status) == SIGINT)
				update_environment(env, "?", ft_itoa(130));
			if (WTERMSIG(exe->status) == SIGQUIT)
				update_environment(env, "?", ft_itoa(131));
			if (WTERMSIG(exe->status) == SIGPIPE)
				update_environment(env, "?", ft_itoa(1));
		}
	}
}

int		handle_pipe_parent(int prev_pipe, t_command **cmd, t_exec *exe)
{
	if (prev_pipe != -1)
		close(prev_pipe);
	if (cmd[exe->i + 1])
	{
		close(exe->pipe_fd[1]);
		prev_pipe = exe->pipe_fd[0];
	}
	exe->pids = exe->pid;
	return (exe->pids);
}

void	exec_command(t_command **cmd, t_env_copy *env)
{
	int		prev_pipe;
	t_exec	exe;

	exe.i = ((exe.pids = 0), (prev_pipe = -1), 0);
	if (!cmd_hard_coded(cmd, env))
		return;
	if (!cmd[1] && !single_builtin(cmd, env))
		return;
	else
	{
		exe.path = find_path(env);
		exe.envp = struct_to_arr_env(env);
		while (cmd[exe.i])
		{
			exe.pid = real_execution(&exe, cmd, env, prev_pipe);
			if (exe.pid > 0)
				exe.pids = handle_pipe_parent(prev_pipe, cmd, &exe);
			exe.i++;
		}
		if (exe.pids)
			wait_for_child(env, cmd, &exe);
	}
}
