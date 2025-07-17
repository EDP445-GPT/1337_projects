/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:27:56 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/16 16:11:19 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	**ft_alocate_args(char *str)
{
	int		i;
	int		j;
	char	**args;
	int		single_qoute;
	int		double_qoute;

	i = ((double_qoute = 0), (single_qoute = 0), (j = 0), 0);
	while (str[i])
	{
		if (str[i] == '\'' && !double_qoute)
			single_qoute = !single_qoute;
		else if (str[i] == '\"' && !single_qoute)
			double_qoute = !double_qoute;
		if ((!single_qoute && !double_qoute) && str[i] != ' '
			&& (str[i + 1] == ' ' || str[i + 1] == '\0'))
			j++;
		i++;
	}
	args = malloc(sizeof(char *) * (j + 2));
	if (!args)
	{
		return (NULL);// free here
	}
	return (args);
}

char	*arg_filler(int i, int j, char *str)
{
	char	*arg;
	char	*s;

	s = ft_substr(str, i, j - i);
	arg = skip_qoute(s);
	free(s);
	return (arg);
}

char	**split_args_filler(char **args, char *str, 
							int single_qoute, int double_qoute)
{
	int	i;
	int	k;
	int	j;

	i = ((k = 0), (j = 0), 0);
	while (str[i])
	{
		while (str[j] == ' ')
			j++;
		i = j;
		while (str[j])
		{
			if (str[j] == ' ' && !single_qoute && !double_qoute)
				break ;
			if (str[j] == '\'' && !double_qoute)
				single_qoute = !single_qoute;
			else if (str[j] == '\"' && !single_qoute)
				double_qoute = !double_qoute;
			j++;
		}
		if (!single_qoute && !double_qoute && j > i)
			args[k++] = arg_filler(i, j, str);
		i = j;
	}
	return ((args[k] = NULL), args);
}

char	**split_args_filler_qoute(char **args, char *str, 
							int single_qoute, int double_qoute)
{
	int	i;
	int	k;
	int	j;

	i = ((k = 0), (j = 0), 0);
	while (str[i])
	{
		while (str[j] == ' ')
			j++;
		i = j;
		while (str[j])
		{
			if (str[j] == ' ' && !single_qoute && !double_qoute)
				break ;
			if (str[j] == '\'' && !double_qoute)
				single_qoute = !single_qoute;
			else if (str[j] == '\"' && !single_qoute)
				double_qoute = !double_qoute;
			j++;
		}
		if (!single_qoute && !double_qoute && j > i)
			args[k++] = ft_substr(str, i, j - i);
		i = j;
	}
	return ((args[k] = NULL), args);
}
