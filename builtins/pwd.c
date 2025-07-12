#include "../header.h"

void ft_pwd(t_env_copy *env)
{
	char *ptr;

	ptr = getcwd(NULL, 0);
	if (ptr)
	{
		printf("%s\n", ptr);
		update_environment(env, "?", "0");
		exit(0);
	}
	else
	{
		perror("pwd");
		update_environment(env, "?", "1");
		exit(1);
	}
}
