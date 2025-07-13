#include "../header.h"
// t_env_copy	*new_env_node(char *name, char *value)
// {
// 	t_env_copy    *tokens;
	
// 	tokens = malloc(sizeof(t_env_copy));
// 	if (!tokens)
// 		return (NULL);
//     tokens->name = name;
// 	tokens->value = value;
// 	tokens->next = NULL;
// 	return (tokens);
// }

// void	add_to_env_list(t_env_copy **env, char *name, char *value)
// {
// 	t_env_copy    *element;
// 	t_env_copy    *temp;

// 	element = new_env_node(name, value);
// 	if (!element)
// 		exit(1);
// 	if ((*env) == NULL)
// 	{
// 		(*env) = element;
// 	}
// 	else
// 	{
// 		temp = *env;
// 		while (temp->next)
// 			temp = temp->next;
// 		temp->next = element;
// 	}
// }
int	ft_isalnum_env(char *s)
{
	int i = 0;
	if (!s[i])
		return (0);
	while (s[i] &&  ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') ||
		 (s[i] == '_') || (s[i] >= '0' && s[i] <= '9')))
	{
		i++;
	}
			
	if (!s[i])
		return (1);
	else
		return (0);
	return (0);
}
void    ft_export(t_command **cmd, t_env_copy *env)
{
    int 	i;
    int 	j;
	int		x;
	char	*value;
	char	*name;

	x = 1;
    j = 0;
    i = 0;
	if (!cmd[0]->args[1])
	{
		while(env)
		{
			if (!env->value)
			{
				printf("declare -x %s\n", env->name);
			}
			else
				printf("declare -x %s=\"%s\"\n", env->name, env->value);
			env = env->next;
		}
	}
	while (cmd[0]->args[x])
	{
		j = 0;
		i = 0;
		while(cmd[0]->args[x] && cmd[0]->args[x][j] && cmd[0]->args[x][j] != '=')
		{
			j++;
		}
		name = ft_substr(cmd[0]->args[x], 0, j);
		if (!ft_isalnum_env(name))
		{
			dprintf(2, "bash: export: `%s': not a valid identifier\n", cmd[0]->args[x]);
			update_environment(env, "?", "1");
			x++;
		}
		else
		{
			j++;
			while(cmd[0]->args[x] && cmd[0]->args[x][i])
			{
				i++;
			}
			if (!(cmd[0]->args[x][j - 1]))
			{
				value = NULL;
			}
			else
				value = ft_substr(cmd[0]->args[x], j, i-j);
			update_environment(env, name, value);
			x++;
		}
	}
    // while(cmd[0]->args[i])
    // {
    // }
}

