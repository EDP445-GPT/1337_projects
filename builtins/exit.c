
#include "../header.h"
#include <ctype.h>

int count_length(char **var)
{
	int i;

	i = 0;
	while(var[i])
		i++;
	return (i);
}

int contain_char(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(!isdigit(str[i]))
			return(1);
		i++;
	}
	return (0);
}

int valid_argument(char **var)
{
	int	length;
	length = count_length(var);
	if (length == 0)
		return (3);
	if(contain_char(var[0]))
		return (1);
	if (length > 1)
		return (0);
	return (2);
}

void ft_exit(char **arguments, t_env_copy *env)
{
	int flag;
	unsigned char c;
	
	printf("exit\n");
	c = 0;
	flag = valid_argument(arguments + 1);
	if (flag == 1)
	{
		printf("exit: %s: numeric argument required\n", arguments[1]);
		update_environment(env, "?", "255");
		exit(255);
	}
	else if (flag == 0)
	{
		printf("exit: too many arguments\n");
		update_environment(env, "?", "2");
		return ;
	}
	else if (flag == 2)
	{
		c = (unsigned char)ft_atoi(arguments[1]);
		char *exit_code = ft_itoa(c);
		update_environment(env, "?", exit_code);
		free(exit_code);
		exit(c);
	}
	else
	{
		update_environment(env, "?", "0");
		exit(0);
	}
}
