/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstclear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:49:50 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/02/02 20:17:15 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_lstclear(t_stack **stack_a)
{
	t_stack	*ptr;

	if (!stack_a)
		return ;
	if (!*stack_a)
		return ;
	while (*stack_a)
	{
		ptr = (*stack_a)->next;
		free(*stack_a);
		*stack_a = ptr;
	}
}
