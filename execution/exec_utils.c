

#include "../header.h"

char	*find_path(t_env_copy *envp)
{
	while(envp)
	{
		if (ft_strcmp("PATH", envp->name) == 0)
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
	
}
// void    free_paths(char **strs)
// {
//     int    i;

//     i = 0;
//     while (strs[i])
//     {
//         free(strs[i]);
//         i++;
//     }
//     free(strs);
// }

char	*check_valid_path(char *path, char *cmd)
{
	int		i;
	char	**sub_paths;
	char	*temp;
	char	*command_path;
	struct 	stat checker;
	char	cwd[MAX_PATH];
	i = 0;
	if (!path)
	{
		getcwd(cwd, sizeof(cwd));
		sub_paths = ft_split(cwd, '/');
		while (sub_paths[i])
		{
			temp = ft_strjoin(sub_paths[i], "/");
			command_path =  ft_strjoin(temp, cmd);
			if (stat(command_path, &checker) == 0 )
			{
			// free(free_paths);
				return (command_path);
			}
		// free(command_path), command_path = NULL;
		i++;
		}
		return cmd;
	}
	sub_paths = ft_split(path, ':');
	if (!sub_paths)
		return (NULL);
	i = 0;

	if (ft_strchr(cmd, '/'))
	{
		if (stat(cmd, &checker) == 0 )
			return (cmd);
		return (NULL);
	}

	while (sub_paths[i])
	{
		temp = ft_strjoin(sub_paths[i], "/");
		command_path =  ft_strjoin(temp, cmd);
		// free(temp);
		if (stat(command_path, &checker) == 0 )
		{
			// free(free_paths);
			return (command_path);
		}
		// free(command_path), command_path = NULL;
		i++;
	}
	return (NULL);
}

