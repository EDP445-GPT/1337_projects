/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:11:16 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/18 15:08:13 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	free_paths(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	*find_path(t_env_copy *envp)
{
	while (envp)
	{
		if (ft_strcmp("PATH", envp->name) == 0)
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

char	*path_unset(char *temp, char *cmd)
{
	struct stat	checker;
	char		cwd[MAX_PATH];
	char		*command_path;

	getcwd(cwd, sizeof(cwd));
	temp = ft_strjoin(cwd, "/");
	command_path = ft_strjoin(temp, cmd);
	free(temp);
	if (stat(command_path, &checker) == 0)
		return (command_path);
	free(command_path);
	return (NULL);
}

char	*path_set(int i, char *temp, char **sub_paths, char *cmd)
{
	struct stat	checker;
	char		cwd[MAX_PATH];
	char		*command_path;

	getcwd(cwd, sizeof(cwd));
	while (sub_paths[i])
	{
		temp = ft_strjoin(sub_paths[i], "/");
		command_path = ft_strjoin(temp, cmd);
		free(temp);
		if (stat(command_path, &checker) == 0)
		{
			return (command_path);
		}
		free(command_path);
		i++;
	}
	return (NULL);
}

char	*check_valid_path(char *path, char *cmd)
{
	int		i;
	char	**sub_paths;
	char	*temp;
	char	*result;

	temp = NULL;
	sub_paths = NULL;
	i = 0;
	if (!path)
		return (path_unset(temp, cmd));
	sub_paths = ft_split(path, ':');
	if (!sub_paths)
		return (NULL);
	result = path_set(i, temp, sub_paths, cmd);
	free_paths(sub_paths);
	return (result);
}
