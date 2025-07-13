
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
	if (str[i] == '+' || str[i] == '-')
		i++;
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
	if(contain_char(var[0]) || !var[0][0])
		return (1);
	if (length > 1)
		return (0);
	return (2);
}

void ft_exit(char **arguments, t_env_copy *env)
{
	int flag;
	unsigned char c;
	
	c = 0;
	flag = valid_argument(arguments + 1);
	printf("exit\n");
	if (flag == 1)
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(arguments[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		update_environment(env, "?", "255");
		exit(255);
	}
	else if (flag == 0)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		update_environment(env, "?", "1");
		return ;
	}
	else if (flag == 2)
	{
		c = ft_atoi(arguments[1]);
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
