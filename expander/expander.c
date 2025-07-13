/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:55:24 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/13 17:56:22 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../header.h"

char *skip_qoute(char *str)
{
	int	i;
	int count;
	int j;
	int	double_flag;
	int	single_flag;

	double_flag = 0;
	single_flag = 0;
	j = 0;
	count = 0;
	i = 0;
	while(str[i])
	{
		if(str[i] == '\'' && !double_flag)
		{
			single_flag = !single_flag;

		}
		else if(str[i] == '\"' && !single_flag)
		{
			double_flag = !double_flag;

		}
		if (str[i] != '\'' &&  str[i] != '\"' )
		{
			count++;
		}
		if (str[i] == '\'' &&  double_flag)
		{
			count++;
		}
		if (str[i] == '\"' &&  single_flag)
		{
			count++;
		}
		
		i++;
	}
	char *s = malloc(sizeof(char ) * (count + 1));
	i =0;
	while(str[i])
	{
		if(str[i] == '\'' && !double_flag)
		{
			single_flag = !single_flag;

		}
		else if(str[i] == '\"' && !single_flag)
		{
			double_flag = !double_flag;

		}
		if (str[i] != '\'' &&  str[i] != '\"' )
		{
			s[j++]=str[i];
		}
		if (str[i] == '\'' &&  double_flag)
		{
			s[j++]=str[i];
		}
		if (str[i] == '\"' &&  single_flag)
		{
			s[j++]=str[i];
		}
		i++;

	}
	if(s)
	{
	s[j] = '\0';
	return (s);
	}
	else 
		return NULL;

}
char *ft_get_env_value(char *name, t_env_copy *env)
{
	while (env)
	{
		if (ft_strcmp(name, env->name) == 0)
			return (env->value);
		env = env->next;
	}
	return NULL;
}
 char *get_var(char *s)
{
	int i;
	int j;
	int var_len;

	j = 0;
	i = 0;
	while(s[i] && s[i] != ' ' && s[i]!= '$' && (ft_isalnum(s[i]) || s[i] == '_' || s[i] == '?')) // stops at not aphanum or underscore or question mark
	{
		i++;
		if(s[i - 1] == '?')
			break ;
	}
	if( i != 0)
	{
		var_len = i;
		char *str = malloc(i + 1);
		i = 0;
		while(i < var_len)
			str[j++] = s[i++];
		str[j] = '\0';
		return str;
	}
	else
		return NULL;
}
/*
	$aa
	i = 1
	""
	
*/
char *ft_expand(char *s, t_env_copy *env)
{
	int	i;
	int single_flag;
	int	double_flag;
	char *tmp;
	i = 0;
   
	
	i = 0;
	single_flag = 0;
	double_flag = 0;
   if(!s)
   {
		return NULL;
   }
	// printf("ff|%s|\n\n\n\n\n", s);

	while(s[i])
	{
		char *var_name;
		if(s[i] == '\'' && !double_flag)
		{
			single_flag = !single_flag;

		}
		else if(s[i] == '\"' && !single_flag)
		{
			double_flag = !double_flag;

		}
		else if ((!single_flag && s[i] == '$') && (ft_isalnum(s[i + 1] )|| s[i + 1] == '_' || s[i + 1] == '?'))
		{
			tmp = ft_substr(s, 0, i);
			var_name = get_var(s + (i + 1));
			if (!ft_get_env_value(var_name, env))
			{
		   		tmp = ft_strjoin(tmp, ft_strdup(" "));
				s = ft_strjoin(tmp, ft_substr(s + i + 1 + ft_strlen(var_name) , 0, ft_strlen(s)));
			}
			else
			{
				tmp = ft_strjoin(tmp, ft_get_env_value(var_name, env));
		   		s = ft_strjoin(tmp, ft_substr(s + i + 1+ ft_strlen(var_name), 0, ft_strlen(s)));
			}
		}
			if(s[i])
				i++;
	}
	return s;
}
char    **ft_split_args(char *str, t_env_copy *env)
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
 	str = ft_expand(str, env);
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
			if (str[j] == ' ')
            j++;
			}
			// if (str[j] == ' ')
            // j++;
        	i = j;
	}
	args[k] = NULL;

	// k=0;
	// while(args[k])
	// {
	// 	printf("|%s|\n", args[k]);
	// 	k++;
	// }
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