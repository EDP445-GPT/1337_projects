#include "../header.h"

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
	if (!cmd[1] && ft_strcmp(cmd[0]->args[0], "export") == 0)
	{
		ft_export(cmd, env);
	}
	else if (!cmd[1] && ft_strcmp(cmd[i]->args[0], "cd") == 0)
		ft_cd(cmd, env);
	else if (!cmd[1] &&  ft_strcmp(cmd[i]->args[0], "unset") == 0)
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
			if ((cmd[i]->args) && (cmd[i]->args[0]))
			{
					command = check_valid_path(path, cmd[i]->args[0]);
					if(!command)
					{
						dprintf(2,"bash: %s: command not found\n", cmd[i]->args[0]);
						update_environment(env, "?", "127");
						return;
					}
			}

			if (cmd[i + 1])
				pipe(fd);
			pid = fork();
			if (pid == 0)
			{
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
					handle_redirection(cmd[i]);
				}
				if ((!cmd[i]->args) || (!cmd[i]->args[0]))
				{
					exit(0);
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
					ft_exit(cmd[0]->args, env);
					exit(0);
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
					// execve(command, cmd[i]->args, envp);
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
			waitpid(pids, &status, 0);
			if (WIFEXITED(status))
				(ft_get_env_node("?", env))->value = ft_itoa(WEXITSTATUS(status));
			while (wait(NULL) > 0)
				;
		}
	}
}
