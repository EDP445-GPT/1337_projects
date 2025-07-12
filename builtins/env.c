/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:42:39 by codespace         #+#    #+#             */
/*   Updated: 2025/07/07 11:28:29 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// void add_env(t_env_copy **env, const char *name, const char *value)
// {
// 	t_env_copy *new_node = malloc(sizeof(t_env_copy));
// 	t_env_copy *temp;

// 	new_node->name = strdup(name);
// 	new_node->value = strdup(value);
// 	new_node->next = NULL;

// 	if (!*env)
// 	{
// 		*env = new_node;
// 		return;
// 	}

// 	temp = *env;
// 	while (temp->next)
// 		temp = temp->next;
// 	temp->next = new_node;
// }

void ft_env(t_env_copy *env)
{
	t_env_copy *ptr;

	ptr = env;
	while(ptr != NULL)
	{
		if(!(ptr->value))
		{
			ptr = ptr->next;
		}
		else
		{
			printf("%s=%s\n", ptr->name, ptr->value);
		}
		if(ptr)
			ptr = ptr->next;
	}
}

// void free_env(t_env_copy *env)
// {
// 	t_env_copy *temp;

// 	while (env)
// 	{
// 		temp = env;
// 		env = env->next;
// 		free(temp->name);
// 		free(temp->value);
// 		free(temp);
// 	}
// }

// // Test function
// int main(void)
// {
// 	t_env_copy *env_list = NULL;

// 	// Add some variables
// 	add_env(&env_list, "USER", "chatgpt");
// 	add_env(&env_list, "HOME", "/home/chatgpt");
// 	add_env(&env_list, "SHELL", "/bin/bash");

// 	printf("=== Current Environment ===\n");
// 	env(env_list);

// 	// Free memory
// 	free_env(env_list);
// 	return 0;
// }