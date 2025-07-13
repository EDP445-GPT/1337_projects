/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:30:55 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/13 18:08:18 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
int cmd_counter(t_tokens *p)
{
	int i;

	i = 1;
	while (p)
	{
		if (p->type == TOKEN_PIPE)
			i++;
		p = p->next;
	}
	return (i);
}

t_command **cmd_allocation(t_tokens *tokens)
{
	int cmd_count = cmd_counter(tokens);
	int args_count;
	int redirs;
	t_tokens *tmp;
	int g;
	t_command **cmd = malloc(sizeof(t_command *) * (cmd_count + 1));
	int v = -1;
	while (++v < cmd_count)
		cmd[v] = malloc(sizeof(t_command));
	cmd[v] = NULL;
	if (!cmd)
		return (perror("malloc failed"), NULL);
	int i = 0;
	t_tokens *start = tokens;

	tmp = start;
	while (i < cmd_count)
	{
		args_count = 0;
		redirs = 0;

		if (tmp->type == TOKEN_PIPE)
		{
			redirs = 0;
			args_count = 0;
			tmp = tmp->next;
		}
		while (tmp && tmp->type != TOKEN_PIPE)
		{
			if (tmp->type == TOKEN_WORD || tmp->type == TOKEN_SINGLE_QUOTE)
				args_count++;
			else if (
				tmp->type == TOKEN_REDIRECT_IN ||
				tmp->type == TOKEN_REDIRECT_OUT ||
				tmp->type == TOKEN_HEREDOC ||
				tmp->type == TOKEN_APPEND_OUT)
				redirs++;
			tmp = tmp->next;
		}
		cmd[i]->args = malloc(sizeof(char *) * (args_count + 1));
		g = 0;
		while (g < args_count + 1)
		{
			cmd[i]->args[g] = NULL;
			g++;
		}
		cmd[i]->redirctions = malloc(sizeof(t_redic *) * (redirs + 1));
		g = 0;
		while (g < redirs)
		{
			cmd[i]->redirctions[g] = malloc(sizeof(t_redic));
			g++;
		}
		g = 0;
		// while (cmd[i]->redirctions && cmd[i]->redirctions[g] && g < redirs + 1)
		// {
		// 	cmd[i]->redirctions[g]->type = -1 ;
		// 	g++;
		// }
		if (!cmd[i]->args || !cmd[i]->redirctions)
			return (perror("malloc failed"), NULL);

		i++;
	}

	return cmd;
}

void ft_parser(t_tokens *tokens, t_env_copy *p)
{
	t_command **cmd;
	int j;
	int k;
	int i;
	char **file;
	char **arguments;
	int arguments_flag;
	t_tokens *tmps = tokens;

	k = 0;
	i = 0;
	j = 0;
	if (!tokens)
		return;
	cmd = cmd_allocation(tokens);
	while (tokens)
	{
		while (tokens && tokens->type != TOKEN_PIPE)
		{
			if ((tokens->type == TOKEN_WORD || tokens->type == TOKEN_SINGLE_QUOTE || tokens->type == TOKEN_DOUBLE_QUOTE))
			{
				cmd[j]->args[0] = ft_strdup(tokens->value);
				// if(tokens->next)
				// 	cmd[j]->args[1] = NULL;
				i++;
			}
			else if (tokens->type == TOKEN_REDIRECT_IN)
			{
				cmd[j]->redirctions[k]->type = IN;
				if (tokens->next)
				{
					arguments_flag = 1;
					arguments = ft_split_args_file(tokens->next->value);
					cmd[j]->redirctions[k]->file = ft_strdup(arguments[0]);
					if (arguments[0][0] == '$')
					{
						cmd[j]->redirctions[k]->file = ft_expand(arguments[0], p);
						file = ft_split_args(cmd[j]->redirctions[k]->file, p);
						// printf("%s", file);
						if (file[1])
						{
							write(2, "ambiguous redirect\n", 20);
							update_environment(p, "?", "1");
						}
					}
					while(arguments[arguments_flag])
					{
						if (cmd[j]->args[0] == NULL)
						{
							cmd[j]->args[0] = ft_strdup(arguments[arguments_flag]);
							arguments_flag++;
							continue ;
						}
						cmd[j]->args[0] = ft_strjoin(cmd[j]->args[0], " ");
						cmd[j]->args[0] = ft_strjoin(cmd[j]->args[0], arguments[arguments_flag]);
						arguments_flag++;
					}
				}
				tokens = tokens->next;
				k++;
			}
			else if (tokens->type == TOKEN_REDIRECT_OUT)
			{
				cmd[j]->redirctions[k]->type = OUT;
				if (tokens->next)
				{
					arguments_flag = 1;
					arguments = ft_split_args_file(tokens->next->value);
					cmd[j]->redirctions[k]->file = ft_strdup(arguments[0]);
					if (arguments[0][0] == '$')
					{
						cmd[j]->redirctions[k]->file = ft_expand(arguments[0], p); // to handle!!!!!!!!!
						file = ft_split_args(cmd[j]->redirctions[k]->file, p);
						if (file[1])
						{
							write(2, "ambiguous redirect\n", 20);
							update_environment(p, "?", "1");
						}
					}
					while(arguments[arguments_flag])
					{
						if (cmd[j]->args[0] == NULL)
						{
							cmd[j]->args[0] = ft_strdup(arguments[arguments_flag]);
							arguments_flag++;
							continue ;
						}
						cmd[j]->args[0] = ft_strjoin(cmd[j]->args[0], " ");
						cmd[j]->args[0] = ft_strjoin(cmd[j]->args[0], arguments[arguments_flag]);
						arguments_flag++;
					}
				}
				tokens = tokens->next;
				k++;
			}
			else if (tokens->type == TOKEN_HEREDOC)
			{
				cmd[j]->redirctions[k]->type = HEREDOC;
				arguments_flag = 1;
				arguments = ft_split_args_file(tokens->next->value);
				cmd[j]->redirctions[k]->file = ft_strdup(arguments[0]);
				if (tokens->next)
				{
					cmd[j]->redirctions[k]->file = ft_strdup(arguments[0]);
					tokens = tokens->next;
					k++;
				}
				while(arguments[arguments_flag])
				{
					if (cmd[j]->args[0] == NULL)
					{
						cmd[j]->args[0] = ft_strdup(arguments[arguments_flag]);
						arguments_flag++;
						continue ;
					}
					cmd[j]->args[0] = ft_strjoin(cmd[j]->args[0], " ");
					cmd[j]->args[0] = ft_strjoin(cmd[j]->args[0], arguments[arguments_flag]);
					arguments_flag++;
				}
			}
			else if (tokens->type == TOKEN_APPEND_OUT)
			{
				cmd[j]->redirctions[k]->type = APPEND;
				if (tokens->next)
				{
					arguments_flag = 1;
					arguments = ft_split_args_file(tokens->next->value);
					cmd[j]->redirctions[k]->file = ft_strdup(arguments[0]);
					if (arguments[0][0] == '$')
					{
						cmd[j]->redirctions[k]->file = ft_expand(arguments[0], p);
						file = ft_split_args(cmd[j]->redirctions[k]->file, p);
						// printf("%s", file);
						if (file[1])
						{
							printf("bash: : ambiguous redirect\n");
							update_environment(p, "?", "1");
						}
					}
					while(arguments[arguments_flag])
					{
						if (cmd[j]->args[0] == NULL)
						{
							cmd[j]->args[0] = ft_strdup(arguments[arguments_flag]);
							arguments_flag++;
							continue ;
						}
						cmd[j]->args[0] = ft_strjoin(cmd[j]->args[0], " ");
						cmd[j]->args[0] = ft_strjoin(cmd[j]->args[0], arguments[arguments_flag]);
						arguments_flag++;
					}
				}
				tokens = tokens->next;
				k++;
			}
			tokens = tokens->next;
		}
		if (tokens && (tokens->type == TOKEN_PIPE))
		{
			// if (cmd[j]->args[0])
			// {
				cmd[j]->args = ft_split_args(cmd[j]->args[0], p);
			// }
			// char **s = cmd[j]->args;
			// int x = 0;
			// while(s[x])
			// {
			// 	printf("%s\n", s[x]);
			// 	x++;
			// }
			cmd[j]->redirctions[k] = NULL;
			// cmd[j]->args[i] = NULL;
			j++;
			tokens = tokens->next;
			k = 0;
			i = 0;
		}
	}
	cmd[j]->redirctions[k] = NULL;
	// cmd[j]->args[i] = NULL;
	k = 0;
	if (cmd[j]->args[0])
	{
		cmd[j]->args = ft_split_args(cmd[j]->args[0], p);
	}
	if(check_herdoc(tmps))
	{
		if (heredoc(cmd, p))
			exec_command(cmd, p);
	}
	else
		exec_command(cmd, p);
	// while (cmd[k] && cmd[k]->args)
	// {
	// 		printf("Command %s:\n", cmd[k]->args[i]);

	// 	// Print args
	// 	 i = 0;
	// 	while ( cmd[k]->args[i])
	// 	{
			// printf("  arg[%d] -> |%s|\n", i, cmd[0]->args[0]);
	// 		i++;
	// 	}
	// 	k++;
	// }
		// exit(1);


	// int x = 0;
				 i = 0;

	// 	// Print redirections
	// 	x = 0;
	// 	// while (cmd[k]->redirctions[x] )
	// 	// {
	// 	// 	printf("  redirection %d:\n", x);
	// 	// 	if(cmd[k]->redirctions[x]->file != NULL)
	// 	// 		printf("    type      -> %d\n", cmd[k]->redirctions[x]->type);
	// 	// 	printf("    file      -> %s\n", cmd[k]->redirctions[x]->file);
	// 	// 	// printf("    delimiter -> %s\n", cmd[k]->redirctions[x]->delimiter ? cmd[k]->redirctions[x]->delimiter : "(none)");
	// 	// 	x++;
	// 	// }
	// 	printf("\n\n");

	// // 	k++;
	// // }
	// while (cmd[2]->redirctions[x] )
	// 	{
	// 		printf("  redirection %d:\n", x);
	// 		if(cmd[k]->redirctions[x]->file != NULL)
	// 			printf("    type      -> %d\n", cmd[k]->redirctions[x]->type);
	// 		printf("    file      -> %s\n", cmd[k]->redirctions[x]->file);
	// 		// printf("    delimiter -> %s\n", cmd[k]->redirctions[x]->delimiter ? cmd[k]->redirctions[x]->delimiter : "(none)");
	// 		x++;
	// 	}
	// exit(0);
}

// // int main ()
// // {
// // 	t_env_copy *p;
// // 	t_tokens *t = tokenizer("ls ffg df df d > a | cd > a > b | pwd -l >  >  >  >  > a ");
// // 	ft_parser(t, p);
// // }