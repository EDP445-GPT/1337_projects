/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_two_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:57:04 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/14 12:44:30 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_tokens	*new_node(int type, char *value)
{
	t_tokens	*tokens;

	tokens = malloc(sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	tokens->type = type;
	tokens->value = value;
	tokens->next = NULL;
	return (tokens);
}

void	add_to_list(t_tokens **tokens, int type, char *value)
{
	t_tokens	*element;
	t_tokens	*temp;

	element = new_node(type, value);
	if (!element)
		exit(1);
	if ((*tokens) == NULL)
	{
		(*tokens) = element;
	}
	else
	{
		temp = *tokens;
		while (temp->next)
			temp = temp->next;
		temp->next = element;
	}
}
