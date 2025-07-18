/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_third.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:17:34 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/18 17:40:35 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "echo") 
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
}

char	**struct_to_arr_env(t_env_copy *env)
{
	int			i;
	char		**envp;
	t_env_copy	*tmp;
	char		*temp;

	i = ((tmp = env), 0);
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

t_env_copy	*ft_get_env_node(char *name, t_env_copy *env)
{
	while (env)
	{
		if (ft_strcmp(name, env->name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	mutiple_builtins(t_command **cmd, int i, t_env_copy *env)
{
	if (ft_strcmp(cmd[i]->args[0], "export") == 0)
		return (ft_export(cmd, env), 0);
	else if ((ft_strcmp(cmd[i]->args[0], "cd") == 0))
		return (ft_cd(cmd, env), 0);
	else if (ft_strcmp(cmd[i]->args[0], "unset") == 0)
		return (ft_unset(env, cmd[0]->args), 0);
	else if (ft_strcmp(cmd[i]->args[0], "exit") == 0)
		return (ft_exit(env, cmd, i), 0);
	else if ((ft_strcmp(cmd[i]->args[0], "pwd") == 0) 
		|| (ft_strcmp(cmd[i]->args[0], "PWD") == 0))
		return (ft_pwd(env, cmd), 0);
	else if ((ft_strcmp(cmd[i]->args[0], "echo") == 0)
		|| (ft_strcmp(cmd[i]->args[0], "ECHO") == 0))
		return (ft_echo(cmd[i]->args), 0);
	else if ((ft_strcmp(cmd[i]->args[0], "env") == 0) 
		|| (ft_strcmp(cmd[i]->args[0], "ENV") == 0))
		return (ft_env(env), 0);
	return (1);
}

int	single_builtin(t_command **cmd, t_env_copy *env)
{
	if (!cmd[1] && ft_strcmp(cmd[0]->args[0], "export") == 0)
		return (ft_export(cmd, env), 0);
	else if (!cmd[1] && ft_strcmp(cmd[0]->args[0], "cd") == 0)
		return (ft_cd(cmd, env), 0);
	else if (!cmd[1] && ft_strcmp(cmd[0]->args[0], "unset") == 0)
		return (ft_unset(env, cmd[0]->args), 0);
	else if (!cmd[1] && ft_strcmp(cmd[0]->args[0], "exit") == 0)
		return (ft_exit(env, cmd, 0), 0); // free here
	return (1);
}
