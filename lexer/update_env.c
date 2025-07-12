/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 10:40:54 by codespace         #+#    #+#             */
/*   Updated: 2025/07/07 12:03:35 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_env_copy	*find_key(t_env_copy *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(key, env->name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
t_env_copy	*find_name(t_env_copy *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(key, env->name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void update_environment(t_env_copy *env, char *key, char *new_value)
{
	t_env_copy *desired_env;
	t_env_copy *ptr;

	
	desired_env = find_key(env, key);
	if (desired_env)
	{
		if (new_value)
		{
			free(desired_env->value);
			desired_env->value = ft_strdup(new_value);
		}
	}
	else
	{
		if (!new_value)
		{
			ptr = lstnew(ft_strdup(key), NULL);
			lstadd_back(&env, ptr);
		}
		else
		{
			ptr = lstnew(ft_strdup(key), ft_strdup(new_value));
			lstadd_back(&env, ptr);
		}
	}
}