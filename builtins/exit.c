/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:07:45 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/18 18:01:56 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	count_length(char **var)
{
	int	i;

	i = 0;
	while (var[i])
		i++;
	return (i);
}

int	contain_char(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	valid_argument(char **var)
{
	int	length;

	length = count_length(var);
	if (length == 0)
		return (3);
	if (contain_char(var[0]) || !var[0][0])
		return (1);
	if (length > 1)
		return (0);
	return (2);
}

void	print_exiterr(char *str, t_env_copy *env, t_command **cmd)
{
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	update_environment(env, "?", "255");
	free_env(env);
	free_cmd(cmd);
	exit(255);
}

void	exit_util_first(t_command **cmd, t_env_copy *env, char *argument)
{
		int		code;

		code = ft_atoi(argument);
		 set_exit_status(env, code);
		free_env(env);
		free_cmd(cmd);
		exit(code);
}
void	ft_exit(t_env_copy *env, t_command **cmd, int i)
{
	int		flag;

	flag = valid_argument(cmd[i]->args + 1);
	printf("exit\n");
	if (flag == 1)
		print_exiterr(cmd[i]->args[1], env, cmd);
	else if (flag == 0)
	{
		stder("bash: exit: too many arguments\n", 2);
		update_environment(env, "?", "1");
		return ;
	}
	else if (flag == 2)
	{
		exit_util_first(cmd, env, cmd[i]->args[1]);
	}
	else
	{
		update_environment(env, "?", "0");
		free_env(env);
		free_cmd(cmd);
		exit(0);
	}
}
