/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 10:55:24 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/16 16:01:09 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	skip_qoute_counter(char *str)
{
	int	i;
	int	double_flag;
	int	single_flag;
	int	count;

	double_flag = ((i = 0), (count = 0), (single_flag = 0), 0);
	while (str[i])
	{
		if (str[i] == '\'' && !double_flag)
			single_flag = !single_flag;
		else if (str[i] == '\"' && !single_flag)
			double_flag = !double_flag;
		if (str[i] != '\'' && str[i] != '\"')
			count++;
		if (str[i] == '\'' && double_flag)
			count++;
		if (str[i] == '\"' && single_flag)
			count++;
		i++;
	}
	return (count);
}

char	*qoute_skipper(char *s, char *str)
{
	int	i;
	int	double_flag;
	int	single_flag;
	int	j;

	double_flag = ((i = 0), (j = 0), (single_flag = 0), 0);
	while (str[i])
	{
		if (str[i] == '\'' && !double_flag)
			single_flag = !single_flag;
		else if (str[i] == '\"' && !single_flag)
			double_flag = !double_flag;
		if (str[i] != '\'' && str[i] != '\"')
			s[j++] = str[i];
		if (str[i] == '\'' && double_flag)
			s[j++] = str[i];
		if (str[i] == '\"' && single_flag)
			s[j++] = str[i];
		i++;
	}
	if (s)
		return (s[j] = '\0', s);
	else
		return (NULL);
}

char	*skip_qoute(char *str)
{
	char	*s;

	s = malloc(sizeof(char) * (skip_qoute_counter(str) + 1));
	if (!s)
	{
		perror("malloc");
		// free here;
	}
	s = qoute_skipper(s, str);
	if (s)
		return (s);
	else
		return (NULL);
}

char	*ft_expand(char *s, t_env_copy *env)
{
	int		single_flag;
	int		double_flag;

	single_flag = 0;
	double_flag = 0;
	if (!s)
		return (NULL);
	s = ft_expand_util(ft_strdup(s), env, single_flag,
			double_flag);
	return (s);
}

char	**ft_split_args(char *str, t_env_copy *env)
{
	char	**args;
	int		single_qoute;
	int		double_qoute;

	double_qoute = 0;
	single_qoute = 0;
	if (!str)
		return (NULL);
	str = ft_expand(str, env);
	args = ft_alocate_args(str);
	args = split_args_filler(args, str, single_qoute, double_qoute);
	if (str)
		free(str);
	return (args);
}
