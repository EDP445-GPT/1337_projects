
#include "../header.h"

t_env_copy *new_node_pwd(char *name, char *value)
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

void    add_to_list_pwd(t_env_copy *env,char *name, char *value)
{
	t_env_copy	*element;
	t_env_copy	*temp;

	element = new_node_pwd(name, value);
	if (!element)
		exit(1);
	if ((env) == NULL)
	{
		(env) = element;
	}
	else
	{
		temp = env;
		while (temp->next)
			temp = temp->next;
		temp->next = element;
	}
}