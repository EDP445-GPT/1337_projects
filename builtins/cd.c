/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:37:37 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/18 18:01:41 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	update_env_pwd(char *new_cwd, t_env_copy *env)
{
	while (env)
	{
		if (ft_strcmp("PWD", env->name) == 0)
		{
			free(env->value);
			env->value = strdup(new_cwd);
			return (0);
		}
		env = env->next;
	}
	return (1);
}

int	update_env_oldpwd(char *old_cwd, t_env_copy *env)
{
	while (env)
	{
		if (ft_strcmp("OLDPWD", env->name) == 0)
		{
			free(env->value);
			env->value = strdup(old_cwd);
			return (0);
		}
		env = env->next;
	}
	return (1);
}

char	*get_home_direc(t_env_copy *env)
{
	while (env)
	{
		if (ft_strcmp("HOME", env->name) == 0)
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

void	ft_cd(t_command **cmd, t_env_copy *env)
{
	char	*old_cwd;
	char	*target;

	old_cwd = getcwd(NULL, 0);
	if (!(cmd[0]->args[1]))
		return (print_cd_err(env));
	else
		target = cmd[0]->args[1];
	if (!check_dir(cmd[0]->args[1], env))
	{
		free(old_cwd);
		return ;
	}
	if (!get_update_cwd(env, target, old_cwd, cmd))
		free(old_cwd);
}
