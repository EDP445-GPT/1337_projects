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
	// i=0;
	// while(envp[i] != NULL)
	// {
	// 	printf("ENVP[%d] -> |%s|\n\n",i, envp[i]);
	// 	i++;
	// }
	// exit(0);
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

void exec_command(t_command **cmd, t_env_copy *env)
{
	pid_t pid;
	char *path;
	char *command;
	int prev_pipe;
	int i;
	int pids;
	int status;
	int fd[2];

	i = 0;
	prev_pipe = -1;
	pids = 0;
	// printf("  arg[%d] -> |%s|\n", i, cmd[0]->args[0]);
if (cmd[0] && (!cmd[0]->args || !cmd[0]->args[0]) && 
	(!cmd[0]->redirctions || !cmd[0]->redirctions[0]) &&
    !cmd[1])
    	return;
	else if (cmd[0] && (!cmd[0]->args || (cmd[0]->args[0] && cmd[0]->args[0][0] == '\0')) &&
		(!cmd[0]->redirctions || !cmd[0]->redirctions[0]) && !cmd[1])
	{
		dprintf(2, "bash: : command not found\n");
		update_environment(env, "?", "127");
		return;
	}
	else if (cmd[0] && (!cmd[0]->args || (cmd[0]->args[0] && cmd[0]->args[0][0] == '.' && cmd[0]->args[0][1] == '\0')) &&
		(!cmd[0]->redirctions || !cmd[0]->redirctions[0]) && !cmd[1])
	{
		dprintf(2, "bash: %s: filename argument required\n", cmd[0]->args[0]);
		dprintf(2, "%s: usage: %s: filename [arguments]\n", cmd[0]->args[0], cmd[0]->args[0]);
		update_environment(env, "?", "2");
		return;
	}

	if (!cmd[1] && ft_strcmp(cmd[0]->args[0], "export") == 0)
	{
		ft_export(cmd, env);
	}
	else if (!cmd[1] && ft_strcmp(cmd[i]->args[0], "cd") == 0)
		ft_cd(cmd, env);

	else if (!cmd[1] && ft_strcmp(cmd[i]->args[0], "unset") == 0)
		ft_unset(env, cmd[i]->args);
	else if (!cmd[1] && ft_strcmp(cmd[i]->args[0], "exit") == 0)
	{
		ft_exit(cmd[0]->args, env);
	}
	else
	{
		path = find_path(env);
		char **envp = struct_to_arr_env(env);

		while (cmd[i])
		{
			// if ((cmd[i]->args) && (cmd[i]->args[0]) && !is_builtin(cmd[i]->args[0]))
			// {
			// 	if (ft_strchr(cmd[i]->args[0], '/'))
        	// 		command = ft_strdup(cmd[i]->args[0]); 
			// 	else
			// 		command = check_valid_path(path, cmd[i]->args[0]);
			// 	if (!command)
			// 	{
			// 		dprintf(2, "bash: %s: command not found\n", cmd[i]->args[0]);
			// 		update_environment(env, "?", "127");
			// 		// return;
			// 	}
			if (cmd[i + 1])
				pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				if (prev_pipe != -1)
				{
					dup2(prev_pipe, STDIN_FILENO);
					close(prev_pipe);
				}
				if (cmd[i + 1])
				{
					dup2(fd[1], STDOUT_FILENO);
					close(fd[1]);

					close(fd[0]);
				}
				if (cmd[i]->redirctions)
				{
						handle_redirection(cmd[i], env);
				}
				if ((!cmd[i]->args) || (!cmd[i]->args[0]))
				{
					exit(0);
				}
				if ((cmd[i]->args) && (cmd[i]->args[0]) && !is_builtin(cmd[i]->args[0]))
			{
				if (ft_strchr(cmd[i]->args[0], '/'))
        			command = ft_strdup(cmd[i]->args[0]); 
				else
					command = check_valid_path(path, cmd[i]->args[0]);
				if (!command)
				{
					dprintf(2, "bash: %s: command not found\n", cmd[i]->args[0]);
					update_environment(env, "?", "127");
					exit(127);
				}
			}
				if (ft_strcmp(cmd[i]->args[0], "export") == 0)
				{
					ft_export(cmd, env);
					exit(0);
				}
				else if ((ft_strcmp(cmd[i]->args[0], "cd") == 0))
				{
					ft_cd(cmd, env);
					exit(0);
				}
				else if (ft_strcmp(cmd[i]->args[0], "unset") == 0)
				{
					ft_unset(env, cmd[i]->args);
					exit(0);
				}
				else if (ft_strcmp(cmd[i]->args[0], "exit") == 0)
				{
					ft_exit(cmd[i]->args, env);
				}
				else if ((ft_strcmp(cmd[i]->args[0], "pwd") == 0) || (ft_strcmp(cmd[i]->args[0], "PWD") == 0))
				{
					ft_pwd(env);
					exit(0);
				}
				else if ((ft_strcmp(cmd[i]->args[0], "echo") == 0) || (ft_strcmp(cmd[i]->args[0], "ECHO") == 0))
				{
					ft_echo(cmd[i]->args);
					exit(0);
				}
				else if ((ft_strcmp(cmd[i]->args[0], "env") == 0) || (ft_strcmp(cmd[i]->args[0], "ENV") == 0))
				{
					ft_env(env);
					exit(0);
				}
				else
				{
					// struct stat st;
					// if (stat(command, &st) == -1 && errno == ENOENT)
					// {
					// 	dprintf(2, "bash: %s: command not found\n", cmd[i]->args[0]);
					// 	update_environment(env, "?", "127");
					// 	exit(126);
					// }
					if (execve(command, cmd[i]->args, envp) == -1)
					{
						if (errno == EISDIR)
							dprintf(2, "bash: %s: is a directory\n", cmd[i]->args[0]);
						else 
							dprintf(2,"bash: %s %s\n", cmd[i]->args[0], strerror(errno)); //change to ft_putstr_fd
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
				}
			}
			else if (pid > 0)
			{
				if (prev_pipe != -1)
					close(prev_pipe);
				if (cmd[i + 1])
				{
					close(fd[1]);
					prev_pipe = fd[0];
				}
				pids = pid;
			}
			i++;
		}
		if (pids)
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			waitpid(pids, &status, 0);
			if (WIFEXITED(status))
				(ft_get_env_node("?", env))->value = ft_itoa(WEXITSTATUS(status));
			while (wait(NULL) > 0)
				;
			signal(SIGINT, signal_handler);
			if (i-1 >= 0 && cmd[i-1]->args && ft_strcmp(cmd[i-1]->args[0], "exit") == 0)
			{
				int code;	
				if (WIFEXITED(status))
				{
					code = WEXITSTATUS(status);
					update_environment(env, "?", ft_itoa(code));
				}
				else
				{
					code = 0;
					update_environment(env, "?", ft_itoa(code));
				}
			}
			else
			{
				if (WIFEXITED(status))
				{
					update_environment(env, "?", ft_itoa(WEXITSTATUS(status)));
				}
				else if (WIFSIGNALED(status))
				{
					printf("\n");
					if (WTERMSIG(status) == SIGINT)
						update_environment(env, "?", ft_itoa(130));
					if (WTERMSIG(status) == SIGQUIT)
						update_environment(env, "?", ft_itoa(131));
					if (WTERMSIG(status)==  SIGPIPE)
					{
						printf("im here\n");
						update_environment(env, "?", ft_itoa(1));
					}
				}
			}
		}
	}
}
