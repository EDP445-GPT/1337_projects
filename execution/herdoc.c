#include "../header.h"

int *open_fd()
{
	char		path[MAX_PATH];
	struct stat	info;
	int			i;
	char		*res;
	int			*fd;

	fd = malloc(sizeof(int) * 2);
	ft_strcpy(path, "/tmp/herdoc");
	i = 0;
	while(1)
	{
		if (stat(path, &info) == 0)
		{
			res = ft_itoa(i);
			my_strcat(path, res);
		}
		else
			break;
		i++;
	}
	fd[0] = open(path, O_CREAT | O_RDWR, 0644);
	fd[1] = open(path, O_RDWR, 0644);
	return (fd);
}

// void sigint_handler()
// {
// 	printf("\n");
// 	exit(1);
// }
#include <termios.h>
void *heredoc(t_command **cmd, t_env_copy *env)
{
	int				*fd;
	pid_t			pid;
	int				i;
	char			*str;
	int				status;
	int				sig;
	struct termios	st;

	tcgetattr(0, &st);
	i = 0;
	while(cmd[i] && cmd[i]->redirctions[0])
	{
		int j = 0;
		while(cmd[i]->redirctions[j] != NULL)
		{
			fd = open_fd();
			if (cmd[i]->redirctions[j]->type == HEREDOC)
			{
				pid = fork();
				if(pid == 0)
				{
					signal(SIGINT, SIG_DFL);
					signal(SIGQUIT, SIG_IGN);
					while (1)
					{
						str = readline("> ");
						if(!str || !ft_strcmp(str, cmd[i]->redirctions[j]->file))
							break ;
						ft_putstr_fd(str, fd[0]);
						ft_putstr_fd("\n", fd[0]);
						free(str);
					}
					close(fd[0]);
					exit(0);
				}
				else
				{
					signal(SIGINT, SIG_IGN);
					waitpid(pid, &status, 0);
					tcsetattr(0, 0, &st);
					signal(SIGINT, signal_handler);
					close(fd[0]);
					if(WIFSIGNALED(status))
					{
						sig = WTERMSIG(status);
						if (sig == SIGINT)
						{
							printf("\n");
							update_environment(env, "?", "1");
							return (NULL) ;
						}
					}
					cmd[i]->redirctions[j]->fd_heredoc = fd[1];
				}
			}
			j++;
		}
		update_environment(env, "?", "0");
		i++;
	}
	return ((void *)31337);
}