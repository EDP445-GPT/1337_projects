#include "../header.h"

char    **ft_split_args_file(char *str)
{
	int		i;
	int		j;
	char	**args;
	int		k;
    int     single_qoute;
    int     double_qoute;
	 
	i = 0;
	j = 0;
	k = 0;
	single_qoute = 0;
	double_qoute = 0;
	if (!str)
		return NULL;
	while(str[i])
	{
		if(str[i] == '\'' && !double_qoute)
		{
			single_qoute = !single_qoute;
		}
		else if(str[i] == '\"' && !single_qoute)
		{
			double_qoute = !double_qoute;
		}
		if((!single_qoute && !double_qoute)  && str[i] != ' ' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
		{
			j++;
		}
		i++;
	}
	single_qoute = 0;
 	double_qoute = 0;
    args = malloc(sizeof(char *) * (j+ 2));
    j = 0;
    i = 0;
	while(str[i])
	{
	   while(str[j] == ' ')
	   {
		j++;
	   }
		i = j;
		while(str[j])
		{
			if (str[j] == ' ' && !single_qoute && !double_qoute)
					break;
			if(str[j] == '\'' && !double_qoute)
			{
				single_qoute = !single_qoute;
			}
			else if(str[j] == '\"' && !single_qoute)
			{
				double_qoute = !double_qoute;
			}
				j++;
		}
			if (!single_qoute && !double_qoute && j > i)
			{
				args[k] = skip_qoute(ft_substr(str, i, j - i));
				k++;
				while(str[j] == ' ')
				{
					j++;
				}
			}
	}
	args[k] = NULL;

	k=0;
	// while(args[k] != NULL)
	// {
	// 	printf("%s\n\n\n", args[k]);
	// 	k++;
	// }
	// exit(1);
return args;
	
}

// int main()
// {
//     char *str = " \"ls\" -la {$a}{'$b'} '$b' \"$a\" |";
//     t_env_copy *p = malloc(sizeof(t_env_copy));
//     p->name = ft_strdup("a");
//     p->value  = ft_strdup("va");
//     p->next  = malloc(sizeof(t_env_copy));
//     p->next->name = ft_strdup("b");
//     p->next->value  = ft_strdup("vb");
//     p->next->next = NULL;
// 	int i =0;
// 	char **args = ft_split_args(str, p);
// 	while(args[i])
// 	{
//     	printf("%s\n",args[i]);
// 		i++;
// 	}
// }



char    **ft_split_args_file_qoute(char *str)
{
	int		i;
	int		j;
	char	**args;
	int		k;
    int     single_qoute;
    int     double_qoute;
	 
	i = 0;
	j = 0;
	k = 0;
	single_qoute = 0;
	double_qoute = 0;
	if (!str)
		return NULL;
	while(str[i])
	{
		if(str[i] == '\'' && !double_qoute)
		{
			single_qoute = !single_qoute;
		}
		else if(str[i] == '\"' && !single_qoute)
		{
			double_qoute = !double_qoute;
		}
		if((!single_qoute && !double_qoute)  && str[i] != ' ' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
		{
			j++;
		}
		i++;
	}
	single_qoute = 0;
 	double_qoute = 0;
    args = malloc(sizeof(char *) * (j+ 2));
    j = 0;
    i = 0;
	while(str[i])
	{
	   while(str[j] == ' ')
	   {
		j++;
	   }
		i = j;
		while(str[j])
		{
			if (str[j] == ' ' && !single_qoute && !double_qoute)
					break;
			if(str[j] == '\'' && !double_qoute)
			{
				single_qoute = !single_qoute;
			}
			else if(str[j] == '\"' && !single_qoute)
			{
				double_qoute = !double_qoute;
			}
				j++;
		}
			if (!single_qoute && !double_qoute && j > i)
			{
				args[k] = ft_substr(str, i, j - i);
				k++;
				while(str[j] == ' ')
				{
					j++;
				}
			}
	}
	args[k] = NULL;

	k=0;
	// while(args[k] != NULL)
	// {
	// 	printf("%s\n\n\n", args[k]);
	// 	k++;
	// }
	// exit(1);
return args;
	
}