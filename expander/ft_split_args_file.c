/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:00:36 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/16 16:07:20 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	**ft_split_args_file(char *str)
{
	char	**args;
	int		single_qoute;
	int		double_qoute;

	double_qoute = 0;
	single_qoute = 0;
	if (!str)
		return (NULL);
	args = ft_alocate_args(str);
	args = split_args_filler(args, str, single_qoute, double_qoute);
	return (args);
}

char	**ft_split_args_file_qoute(char *str)
{
	char	**args;
	int		single_qoute;
	int		double_qoute;

	double_qoute = 0;
	single_qoute = 0;
	if (!str)
		return (NULL);
	args = ft_alocate_args(str);
	args = split_args_filler_qoute(args, str, single_qoute, double_qoute);
	return (args);
}
