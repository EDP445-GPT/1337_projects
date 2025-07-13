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
	int	flag = 0;

	i = 1;
	if (!argument[i])
	{
		printf("\n");
	}
	else
	{
	if((is_valid_flag(argument[i])) == 1)
	{
		flag = 1;
	}
	while((is_valid_flag(argument[i])) == 1)
		i++;
	if (flag == 1)
	{
		// i++;
		while(argument[i])
		{
			printf("%s", argument[i]);
			if(argument[i + 1])
				printf(" ");

			i++;
		}
	}
	else if(flag == 0)
	{
		while(argument[i])
		{
			printf("%s", argument[i]);
			if(argument[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
	}
	}

}