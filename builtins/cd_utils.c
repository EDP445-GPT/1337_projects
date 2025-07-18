/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:21:15 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/18 13:41:40 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_env_copy	*new_node_pwd(char *name, char *value)
{
	t_env_copy	*tokens;

	tokens = malloc(sizeof(t_env_copy));
	if (!tokens)
		return (NULL);
	tokens->name = name;
	tokens->value = value;
	tokens->next = NULL;
	return (tokens);
}

void	add_to_list_pwd(t_env_copy *env, char *name, char *value,
				t_command **cmd)
{
	t_env_copy	*element;
	t_env_copy	*temp;

	element = new_node_pwd(name, value);
	if (!element)
	{
		free_cmd(cmd);
		free_env(env);
		free(name);
		free(value);
		exit(1);
	}
	// if (name)
	// 	free(name);
	// if (value)
	// 	free(value);
	if (env == NULL)
		env = element;
	else
	{
		temp = env;
		while (temp->next)
			temp = temp->next;
		temp->next = element;
	}
}

void	print_cd_err(t_env_copy *env)
{
	char	*target;

	target = get_home_direc(env);
	if (!target)
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		update_environment(env, "?", "1");
		return ;
	}
	if (*target == 0)
	{
		update_environment(env, "?", "0");
		return ;
	}
}

int	check_dir(char *str, t_env_copy *env)
{
	struct stat	check;

	if (stat(str, &check) == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		update_environment(env, "?", "1");
		return (0);
	}
	if (!S_ISDIR(check.st_mode))
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Not a directory\n", 2);
		update_environment(env, "?", "1");
		return (0);
	}
	return (1);
}

int	get_update_cwd(t_env_copy *env, char *target, char *old_cwd, t_command **cmd)
{
	char	new_cwd[MAX_PATH];

	if (chdir(target) != 0)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(target, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		update_environment(env, "?", "1");
		return (0);
	}
	if (!getcwd(new_cwd, sizeof(new_cwd)))
	{
		perror("bash: cd: getcwd failed");
		update_environment(env, "?", "1");
		return (0);
	}
	if (update_env_pwd(new_cwd, env))
		add_to_list_pwd(env, ft_strdup("PWD"), ft_strdup(new_cwd), cmd);
	if (update_env_oldpwd(old_cwd, env))
		add_to_list_pwd(env, ft_strdup("OLDPWD"), ft_strdup(old_cwd), cmd);
	update_environment(env, "?", "0");
	return (1);
}
