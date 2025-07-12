#include "../header.h"

int is_valid_flag(char *str)
{
	int i;
	if (!str)
		return (2);
	if (*str != '-')
		return (-1);
	else
	{
		i = 1;
		while(str[i] == 'n' && str[i])
			i++;
		if(str[i] == 0)
			return (1);
		else
			return (0);
	}
}


void ft_echo(char **argument)
{
	int	i;
	int	flag;

	i = 1;
	while((flag = is_valid_flag(argument[i])) == 0)
		i++;
	if (flag == 1)
	{
		i++;
		while(argument[i])
		{
			printf("%s", argument[i]);
			i++;
		}
	}
	else if(flag == -1)
	{
		while(argument[i])
		{
			printf("%s", argument[i]);
			i++;
		}
		printf("\n");
	}
	else
		printf("\n");
}