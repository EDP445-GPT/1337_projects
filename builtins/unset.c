/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 04:17:56 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/17 16:03:17 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	is_valid_var_name(char *var)
{
	int	i;

	i = 0;
	if (var[i] == '$')
		i++;
	if (var[0] == '-')
	{
		ft_putstr_fd("bash: unset: ", 2);
		ft_putchar_fd(var[0], 2);
		ft_putchar_fd(var[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (-1);
	}
	if (!var || (!isalpha(var[0]) && var[0] != '_'))
		return (0);
	while (var[i])
	{
		if (!(isalnum(var[i]) || var[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset(t_env_copy *env, char **var)
{
	int			i;
	t_env_copy	*node;

	i = 1;
	while (var[i])
	{
		if (is_valid_var_name(var[i]) == -1)
		{
			update_environment(env, "?", "2");
			return ;
		}
		if (is_valid_var_name(var[i]) == 0)
		{
			stder("bash: unset: `", 2);
			stder(var[i], 2);
			stder("': not a valid identifier\n", 2);
			update_environment(env, "?", "1");
			return ;
		}
		node = find_key(env, var[i]);
		if (node)
			lst_delete_node(&env, node);
		i++;
	}
	update_environment(env, "?", "0");
}
