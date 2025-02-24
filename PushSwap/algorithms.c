/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:33:13 by codespace         #+#    #+#             */
/*   Updated: 2025/02/24 09:52:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	position(t_stack **stack_a)
{
	t_stack	*tmp;
	int		i;

	tmp = *stack_a;
	i = 0;
	while(tmp)
	{
		tmp->pos = i;
		i++;
		tmp = tmp->next;
	}
}

void	indexing(t_stack **stack_a)
{
	t_stack	*tmp;
	t_stack	*another_tmp;

	tmp = *stack_a;
	another_tmp = *stack_a;
	while(tmp)
	{
		another_tmp = *stack_a;
		while(another_tmp)
		{
			if(another_tmp->data < tmp->data)
				(tmp->idx)++;
			another_tmp = another_tmp->next;
		}
		tmp = tmp->next;
	}
}

void	pushing_b(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmpa;
	int		length_a;
	int		range;
	int		i;

	length_a = ft_lstsize(*stack_a);
	range = 0.048 * length_a + 10;
	tmpa = *stack_a;
	i = 0;
	while(tmpa)
	{
		if(tmpa->idx >= i && tmpa->idx <= (i + range))
			pb(stack_a, stack_a);
		else if(tmpa->idx < i)
		{
			pb(stack_a, stack_b);
			rb(stack_b);
		}
		else
			ra(stack_a);
		tmpa = tmpa->next;
		i++;
	}
}