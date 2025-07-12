
#include "../header.h"

int is_valid_var_name(char *var)
{
	int i = 0;
	if (!var || (!isalpha(var[0]) && var[0] != '_'))
		return (0);
	i = 1;
	while(var[i])
	{
		if (!(isalpha(var[i]) || var[i] == '_'))
			return (0);
		i++;
	}
	return(1);
}

void ft_unset(t_env_copy *env, char **var)
{
	int			i;
	t_env_copy	*node;

	i = 1;
	while(var[i])
	{
	if (!is_valid_var_name(var[i]))
	{
		printf("unset: `%s': not a valid identifier\n", var[i]);
		update_environment(env, "?", "1");
		// exit(1);
		return ;//!to be fixed
	}
	node = find_key(env, var[i]);
	if (node)
		lst_delete_node(&env, node);
		i++;
	}
	update_environment(env, "?", "0");
}


// void add_node(t_env_copy **env, char *name, char *value)
// {
//     t_env_copy *new_node = malloc(sizeof(t_env_copy));
//     t_env_copy *temp = *env;

//     new_node->name = strdup(name);
//     new_node->value = strdup(value);
//     new_node->next = NULL;

//     if (!*env)
//     {
//         *env = new_node;
//         return;
//     }

//     while (temp->next)
//         temp = temp->next;
//     temp->next = new_node;
// }

// // Helper to print the list
// void print_env(t_env_copy *env)
// {
//     while (env)
//     {
//         printf("%s=%s\n", env->name, env->value);
//         env = env->next;
//     }
// }

// int main()
// {
//     t_env_copy *env = NULL;

//     // Create some env variables
//     add_node(&env, "USER", "chatgpt");
//     add_node(&env, "PATH", "/usr/bin");
//     add_node(&env, "HOME", "/home/chatgpt");
//     add_node(&env, "SHELL", "/bin/bash");

//     printf("Before unset:\n");
//     print_env(env);

//     // Simulate command: unset PATH HOME
//     char *unset_cmd[] = {"unset", "PATH", "H!OME", "JBELKERF", NULL};
//     unset(env, unset_cmd);

//     printf("\nAfter unset:\n");
//     print_env(env);

//     // Free remaining list nodes here (not shown)

//     return 0;
// }
