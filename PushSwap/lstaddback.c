/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstaddback.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaarafi <mmaarafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:06:43 by mmaarafi          #+#    #+#             */
/*   Updated: 2025/02/02 19:38:31 by mmaarafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_lstadd_back(t_stack **stack_a, t_stack *new)
{
	t_stack	*ptr;
	t_stack	*another_ptr;

	if (!stack_a || !new)
		return ;
	if (*stack_a == NULL)
	{
		*stack_a = new;
		return ;
	}
	ptr = *stack_a;
	while (ptr != NULL)
	{
		another_ptr = ptr;
		ptr = ptr->next;
	}
	another_ptr->next = new;
}
