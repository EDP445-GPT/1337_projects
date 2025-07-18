/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:25:45 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/18 15:20:43 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*ft_get_env_value(char *name, t_env_copy *env)
{
	while (env)
	{
		if (ft_strcmp(name, env->name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*get_var(char *s)
{
	int		i;
	int		j;
	int		var_len;
	char	*str;

	j = ((i = 0), 0);
	while (s[i] && s[i] != ' ' && s[i] != '$' && (ft_isalnum(s[i])
			|| s[i] == '_' || s[i] == '?'))
	{
		i++;
		if (s[i - 1] == '?')
			break ;
		if (ft_isdigit(s[i - 1]))
			break ;
	}
	if (i == 0)
		return (NULL);
	var_len = i;
	str = malloc(i + 1);
	i = 0;
	while (j < var_len)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_expand_result(char *s, int i, char *var_name, t_env_copy *env)
{
	char	*tmp;
	char	*var_value;
	char	*result;
	char	*tmp2;
	char	*substr_free;

	tmp = ft_substr(s, 0, i);
	var_value = ft_get_env_value(var_name, env);
	if (!var_value)
	{
		tmp2 = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		tmp2 = ft_strjoin(tmp, var_value);
		free(tmp);
	}
	substr_free = ft_substr(s + i + 1 + ft_strlen(var_name), 0, ft_strlen(s));
	result = ft_strjoin(tmp2, substr_free);
	free(tmp2);
	free(s);
	free(substr_free);
	return (result);
}

char	*ft_expand_util(char *s, t_env_copy *env, int single_flag,
						int double_flag)
{
	char	*var_name;
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !double_flag)
			single_flag = !single_flag;
		else if (s[i] == '\"' && !single_flag)
			double_flag = !double_flag;
		else if ((!single_flag && s[i] == '$') 
			&& (ft_isalnum(s[i + 1]) || s[i + 1] == '_' || s[i + 1] == '?'))
		{
			var_name = get_var(s + (i + 1));
			s = ft_expand_result(s, i, var_name, env);
			free(var_name);
		}
		if (s[i])
			i++;
	}
	return (s);
}
