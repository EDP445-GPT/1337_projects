#include "header.h"

void	rra(t_stack **stack)
{
	t_stack	*tmp;
	t_stack *ptr;

	if (!stack || !(*stack) || !((*stack)->next))
		return ;
	ptr = *stack;
	while(ptr)
	{
		if((ptr->next)->next == NULL)
		{
			tmp = ptr->next;
			ptr->next = NULL;
			break;
		}
		ptr = ptr->next;
	}
	ft_lstadd_front(stack, tmp);
	write(1, "rra\n", 3);
}

void	rrb(t_stack **stack)
{
	t_stack	*tmp;
	t_stack *ptr;

	if (!stack || !(*stack) || !((*stack)->next))
		return ;
	ptr = *stack;
	while(ptr)
	{
		if((ptr->next)->next == NULL)
		{
			tmp = ptr->next;
			ptr->next = NULL;
			break;
		}
		ptr = ptr->next;
	}
	ft_lstadd_front(stack, tmp);
	write(1, "rrb\n", 3);
}

void	rrr(t_stack **stacka, t_stack **stackb)
{
	rrotate(stacka);
	rrotate(stackb);
	write(1, "rrr\n", 3);
}
