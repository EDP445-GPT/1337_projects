/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:07:25 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/07/14 13:08:25 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_env_copy	*lstnew(char *name, char *value)
{
	t_env_copy	*head;

	head = malloc(sizeof(t_env_copy));
	if (head == NULL)
		return (NULL);
	head->name = name;
	if (value)
		head->value = value;
	else
		head->value = NULL;
	head->next = NULL;
	return (head);
}

void	lstadd_back(t_env_copy **lst, t_env_copy *new)
{
	t_env_copy	*ptr;
	t_env_copy	*another_ptr;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr != NULL)
	{
		another_ptr = ptr;
		ptr = ptr->next;
	}
	another_ptr->next = new;
}

void	lst_delete_node(t_env_copy **lst, t_env_copy *node)
{
	t_env_copy	*ptr;

	if (!lst ||!*lst || !node)
		return ;
	ptr = *lst;
	if (ptr == node)
	{
		*lst = node->next;
		free(node->name);
		free(node->value);
		free(node);
		return ;
	}
	while (ptr != NULL)
	{
		if (ptr->next == node)
		{
			ptr->next = node->next;
			free(node->name);
			free(node->value);
			free(node);
			return ;
		}
		ptr = ptr->next;
	}
}
