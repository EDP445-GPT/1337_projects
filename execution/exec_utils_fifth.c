/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_fifth.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:32:56 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/18 16:15:43 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	set_exit_status(t_env_copy *env, int exit_status)
{
	char *code = ft_itoa(exit_status);
	update_environment(env, "?", code);
	free(code);
}

void	free_cmd_env(t_command **cmd, t_env_copy *env)
{
	free_env(env);
	free_cmd(cmd);
}
void	free_envp_array(char **envp)
{
	int	i;
	i = 0;
	if (!envp) 
		return ;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}