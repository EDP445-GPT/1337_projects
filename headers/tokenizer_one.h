/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_one.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:52:10 by codespace         #+#    #+#             */
/*   Updated: 2025/07/01 20:29:26 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_ONE_H

#define TOKENIZER_ONE_H


#include <stdlib.h>
#include "../includes/libft/libft.h"


typedef enum {
	TOKEN_WORD,			// command or argument
	TOKEN_PIPE, 		// |
	TOKEN_REDIRECT_IN,		// <
	TOKEN_REDIRECT_OUT,		// >
	TOKEN_APPEND_OUT,		// >>
	TOKEN_HEREDOC,			// <<
	TOKEN_SINGLE_QUOTE,		// ' (not as a token itself, but when inside quoted word)
	TOKEN_DOUBLE_QUOTE,		// " (same as above)
	TOKEN_ENV_VAR,			// $VAR
	TOKEN_EXIT_STATUS,		// $?
	TOKEN_EOF,
	TOKEN_ERROR
} TokenType;


typedef struct s_tokens
{
	TokenType		type;
	char			*value;
	struct s_tokens	*next;
}	t_tokens;

char		**custom_split(char const *s);
//int			new_node(t_tokens **tokens, int type, char *value);
t_tokens		*new_node(int type, char *value);
void		add_to_list(t_tokens **tokens, int type, char *value);
int			is_pipe(char *str);
int			is_redirect_in(char *str);
int			is_redirect_out(char *str);
int			is_heredoc(char *str);
int			is_append_out(char *str);
int			is_single_q(char *str);
t_tokens	*tokenizer(char *str);


#endif
