/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:58:35 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/18 10:58:53 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	handle_child(char *delimiter, int *fd, t_env_copy *env)
{
	char	*str;
	char	*another_str;
	int		expansion_flag;
	char	**args;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	expansion_flag = delimiter_check(delimiter);
	args = ft_split_args_file(delimiter);
	delimiter = args[0];
	while (1)
	{
		str = readline("> ");
		if (!str || !ft_strcmp(str, delimiter))
			break ;
		if (!expansion_flag)
			another_str = ft_expand_herdoc(str, env);
		else
			another_str = str;
		stder(another_str, fd[0]);
		stder("\n", fd[0]);
		free(str);
	}
	close(fd[0]);
	exit(0);
}

void	*handle_parent_signal(t_env_copy *env, int status)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			printf("\n");
			update_environment(env, "?", "1");
			return (NULL);
		}
	}
	return ((void *)1);
}

void	*herdoc_function(t_env_copy *env, char *delimiter, int *herdoc_fd)
{
	int				*fd;
	pid_t			pid;
	int				status;
	struct termios	st;

	tcgetattr(0, &st);
	fd = open_fd();
	pid = fork();
	if (pid == 0)
		handle_child(delimiter, fd, env);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		tcsetattr(0, 0, &st);
		signal(SIGINT, signal_handler);
		close(fd[0]);
		if (handle_parent_signal(env, status) == NULL)
			return (NULL);
		*herdoc_fd = fd[1];
	}
	free(fd); // change here
	return ((void *)1);
}

void	*heredoc(t_command **cmd, t_env_copy *env)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		if (!cmd[i]->redirctions[0])
		{
			i++;
			continue ;
		}
		j = 0;
		while (cmd[i]->redirctions[j] != NULL)
		{
			if (cmd[i] && cmd[i]->redirctions 
				&& cmd[i]->redirctions[j]->type == HEREDOC)
				if (herdoc_function(env, cmd[i]->redirctions[j]->file,
						&cmd[i]->redirctions[j]->fd_heredoc) == NULL)
					return (NULL);
			j++;
		}
		update_environment(env, "?", "0");
		i++;
	}
	return ((void *)31337);
}
