#include "header.h"

void	rrotate(t_stack **stack)
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
}

void	rrotate_both(t_stack **stacka, t_stack **stackb)
{
	rrotate(stacka);
	rrotate(stackb);
}
