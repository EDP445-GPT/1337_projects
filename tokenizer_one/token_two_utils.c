/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_two_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:57:04 by mboutahi          #+#    #+#             */
/*   Updated: 2025/07/09 18:01:41 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// int	new_node(t_tokens **tokens, int type, char *value)
// {
// 	*tokens = malloc(sizeof(t_tokens));
// 	if (!(*tokens))
// 		return (-1);
//     (*tokens)->type = type;
// 	(*tokens)->value = value;
// 	(*tokens)->next = NULL;
// 	return (1);
// }

// void	add_to_list(t_tokens **tokens, int type, char *value)
// {
// 	t_tokens    *element;
// 	t_tokens     *temp;

// 	printf("type: [%d] value: [%s]", type, value);
// 	element = NULL;
// 	if (new_node(&element, type, value) == -1)
//     {
//         //free here
// 		exit(1);
//     }
// 	if (tokens && (*tokens) == NULL)
// 	{
// 		(*tokens) = element;
// 	}
// 	else
// 	{
// 		temp = *tokens;
// 		while (temp->next)
// 			temp = temp->next;
// 		temp->next = element;
// 	}
// }

t_tokens *new_node(int type, char *value)
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

void add_to_list(t_tokens **tokens, int type, char *value)
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
