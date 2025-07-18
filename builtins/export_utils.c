/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 04:08:35 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/18 15:54:50 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	ft_isalnum_env(char *s)
{
	int	i;

	i = 0;
	if (!s[i])
		return (0);
	if (s[0] == '-')
	{
		dprintf(2, "bash: export: %c%c: invalid option\n", s[0], s[1]);
		return (-1);
	}
	if (!s || (!isalpha(s[0]) && s[0] != '_'))
		return (0);
	while (s[i])
	{
		if (!s || (!isalnum(s[i]) && s[i] != '_'))
			return (0);
		i++;
	}
	while (s[i] && ((s[i] >= 'a' && s[i] <= 'z') 
			|| (s[i] >= 'A' && s[i] <= 'Z') || (s[i] == '_')))
		i++;
	if (!s[i])
		return (1);
	return (0);
}

void	print_export(t_env_copy *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, "?") == 0)
		{
			env = env->next;
			continue ;
		}
		if (!env->value)
			printf("declare -x %s\n", env->name);
		else
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
		env = env->next;
	}
}

void	print_invalid_export_option(char *name, t_env_copy *env)
{
	ft_putstr_fd("bash: export: ", 2);
	ft_putchar_fd(name[0], 2);
	ft_putchar_fd(name[1], 2);
	ft_putstr_fd(": invalid option\n", 2);
	update_environment(env, "?", "2");
	free(name);
}

void	print_invalid_export_id(char *name, t_env_copy *env)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	update_environment(env, "?", "1");
	free(name);
}

void	export_args(t_env_copy *env, char *value, int j, char *args)
{
	int		i;
	char	*name;

	j = ((i = 0), 0);
	while (args && args[j] && args[j] != '=')
		j++;
	name = ft_substr(args, 0, j);
	if (name[0] == '-')
		print_invalid_export_option(name, env);
	else if (!ft_isalnum_env(name))
		print_invalid_export_id(name, env);
	else
	{
		j++;
		while (args && args[i])
			i++;
		if (!args[j - 1])
			value = NULL;
		else
			value = ft_substr(args, j, i - j);
		update_environment(env, name, value);
		free(name);
		if (value)
			free(value);
	}
}
