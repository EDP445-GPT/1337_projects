

#include "../header.h"
#include <stdio.h>

int is_word(char *str)
{
	int i;

	i = 0;
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		return (0);
	return (1);
}

int is_single_q(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int is_double_q(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

t_tokens	 *tokenizer(char *str)
{
	t_tokens	*tokens;
	char		**args;
	int			i;
	int			type;
	char		*value;

	i = 0;
	tokens = NULL;
	args = custom_split(str);
	while (args[i] != NULL)
	{
		if (is_word(args[i]))
		{
		// printf("here 00 \n");
			if (is_single_q(args[i]))
			{
				type = TOKEN_SINGLE_QUOTE;
				value = args[i];

				add_to_list(&tokens, type, value); 
			}
			else if (is_double_q(args[i]))
			{
				type = TOKEN_DOUBLE_QUOTE;
				value = args[i];
				// printf(" skgsjskjhs\n");
				add_to_list(&tokens, type, value);
			}
			else
			{
				type = TOKEN_WORD;
				value = args[i];
				add_to_list(&tokens, type, value);
			}
		}
		else if (is_pipe(args[i]))
		{
			type = TOKEN_PIPE;
			value = args[i];

			add_to_list(&tokens, type, value);
		}
		else if (is_redirect_in(args[i]))
		{
			
			type = TOKEN_REDIRECT_IN;
			value = args[i];

			add_to_list(&tokens, type, value);
		}
		else if (is_redirect_out(args[i]))
		{
			type = TOKEN_REDIRECT_OUT;
			value = args[i];

			add_to_list(&tokens, type, value);
		}
		else if (is_heredoc(args[i]))
		{
			type = TOKEN_HEREDOC;
			value = args[i];

			add_to_list(&tokens, type, value);
		}
		else if (is_append_out(args[i]))
		{
			type = TOKEN_APPEND_OUT;
			value = args[i];

			add_to_list(&tokens, type, value);
		}		
		i++;
	}
	// t_tokens *yo = tokens;
	// while(yo)
	// {
	// 	printf("\n|%s|\n", yo->value);
	// 	yo = yo->next;
	// }
	return (tokens);
}
