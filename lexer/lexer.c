#include "../header.h"

void	free_tokens(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

int check_quotes(char *str)
{
	int i;
	char c;

	i = 0;
	while(str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			c = str[i];
			i++;
			while(str[i] != c && str[i])
				i++;
			if (!str[i])
				return (0);
		}
		i++;
	}
	return (1);
}

int is_redirection_token(char *token)
{
	return (strcmp(token, ">") == 0 || strcmp(token, "<") == 0 || 
			strcmp(token, ">>") == 0 || strcmp(token, "<<") == 0);
}

int is_pipe_token(char *token)
{
	return (strcmp(token, "|") == 0);
}

int is_special_token(char *token)
{
	return (is_pipe_token(token) || is_redirection_token(token));
}
int	is_only_space(char *token)
{
	int	i;
	i=0;
	while(token[i])
	{
		if(token[i] != ' ')
			return 0;
		i++;
	}
		return 1;
}

int check_pipes(char **tokens)
{
	int i;

	i = 0;
	// if (tokens[0] && is_pipe_token(tokens[0]))
	// {
	// 	printf("syntax error near unexpected token `|'\n");
	// 	return (0);
	// }
	
	while(tokens[i])
	{
		if (is_pipe_token(tokens[i]))
		{
			if ((i - 1) < 0)
			{
				printf("syntax error near unexpected token `|'\n");
				return (0);
			}
			if (!tokens[i + 1])
			{
				printf("syntax error near unexpected token `newline'\n");
				return (0);
			}
			if (is_pipe_token(tokens[i + 1]))
			{
				printf("syntax error near unexpected token `||'\n");
				return (0);
			}
			if (is_redirection_token(tokens[i + 1]))
			{
				printf("syntax error near unexpected token `%s'\n", tokens[i + 1]);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int check_redirections(char **tokens)
{
	int i;

	i = 0;
	// printf("%s", tokens[i]);
	while(tokens[i])
	{
		if (is_redirection_token(tokens[i]))
		{
			if (!tokens[i + 1])
			{
				printf("syntax error near unexpected token `newline'\n");
				return (0);
			}
			if (is_pipe_token(tokens[i + 1]))
			{
				printf("syntax error near unexpected token `|'\n");
				return (0);
			}
			if (is_redirection_token(tokens[i + 1]))
			{
				printf("syntax error near unexpected token `%s'\n", tokens[i + 1]);
				return (0);
			}
			if(is_only_space(tokens[i + 1]))
			{
				printf("syntax error near unexpected token `%s'\n", tokens[i + 2]);
				return (0);
			}
		}
		if (strcmp(tokens[i], ">") == 0 && tokens[i + 1] && strcmp(tokens[i + 1], ">") == 0)
		{
			printf("syntax error near unexpected token `>'\n");
			return (0);
		}
		if (strcmp(tokens[i], "<") == 0 && tokens[i + 1] && strcmp(tokens[i + 1], "<") == 0)
		{
			printf("syntax error near unexpected token `<'\n");
			return (0);
		}
		i++;
	}
	return (1);
}

// int is_empty_input(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

int lexer(char *str, t_env_copy *env)
{
	char	**tokens;
	int		i;

	i = 0;
	if (!str)
		return (1);

	if (!check_quotes(str))
	{
		printf("syntax error: unclosed quotes\n");
		update_environment(env, "?", "1");
		return (0);
	}

	tokens = lexer_custom_split(str);
	// while(tokens[i])
	// {
	// 	printf("|%s|\n", tokens[i]);
	// 	i++;
	// }
	if (!tokens)
	{
		update_environment(env, "?", "1");
		return (0);
	}
	if (!tokens[0])
	{
		free_tokens(tokens);
		return (1);
	}
		if (!check_pipes(tokens))
		{
			update_environment(env, "?", "258");
			free_tokens(tokens);
			return (0);
		}
		 if (!check_redirections(tokens))
		{
			update_environment(env, "?", "258");
			free_tokens(tokens);
			return (0);
		}
	free_tokens(tokens);
	return (1);
}